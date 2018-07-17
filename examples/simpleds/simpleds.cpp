#include <memory>

#include <QByteArray>
#include <QResource>
#include <QApplication>

#include "simpleds.hpp"
#include "scandialog.hpp"
#include "twglue.hpp"

using namespace Twpp;
using namespace std::placeholders;

TWPP_ENTRY(SimpleDs)

static constexpr const Identity srcIdent(
        Version(1, 0, Language::English, Country::CzechRepublic, "v1.0"),
        DataGroup::Image,
        "Martin Richter",
        "Examples",
        "Simple TWPP data source"
#if defined(_MSC_VER)
            " MSVC"
#elif defined(__GNUC__)
            " GCC"
#elif defined(__clang__)
            " CLang"
#endif
    );

// lets just simulate uniform resolution for both axes
static constexpr UInt32 RESOLUTION = 85;

static int argc = 0;
static char** argv = nullptr;
static QByteArray bmpData;
static std::unique_ptr<QApplication> application;
static std::unique_ptr<ScanDialog> scanDialog;

#if TWPP_DETAIL_OS_WIN
static std::unique_ptr<QWidget> guiBridge;
#endif

const Identity& SimpleDs::defaultIdentity() noexcept{
    // remember, we return a reference, therefore the identity must not be placed on the stack of this method
    return srcIdent;
}

Result SimpleDs::call(const Identity& origin, DataGroup dg, Dat dat, Msg msg, void* data){
    try {
        // we can override almost anything from SourceFromThis, even the top-most source instance call
        return Base::call(origin, dg, dat, msg, data);
    } catch (const CapabilityException&){
        return badValue();
    }
}

// some helper functions to handle capability stuff
template<typename T>
static Result oneValGet(Msg msg, Capability& data, const T& value){
    switch (msg){
        case Msg::Get:
        case Msg::GetCurrent:
        case Msg::GetDefault:
            data = Capability::createOneValue(data.type(), value);
            return {};

        default:
            return {ReturnCode::Failure, ConditionCode::CapBadOperation};
    }
}

template<typename T>
static Result enmGet(Msg msg, Capability& data, const T& value){
    switch (msg){
        case Msg::Get:
            data = Capability::createEnumeration(data.type(), {value});
            return {};
        case Msg::GetCurrent:
        case Msg::GetDefault:
            data = Capability::createOneValue(data.type(), value);
            return {};

        default:
            return {ReturnCode::Failure, ConditionCode::CapBadOperation};
    }
}

template<typename T>
static Result oneValGetSet(Msg msg, Capability& data, T& value, const T& def){
    switch (msg){
        case Msg::Reset:
            value = def;
            // fallthrough
        case Msg::Get:
        case Msg::GetCurrent:
            data = Capability::createOneValue(data.type(), value);
            return {};

        case Msg::GetDefault:
            data = Capability::createOneValue(data.type(), def);
            return {};

        case Msg::Set:
            value = data.currentItem<T>();
            return {};

        default:
            return {ReturnCode::Failure, ConditionCode::CapBadOperation};
    }
}

template<typename T>
static Result oneValGetSetConst(Msg msg, Capability& data, const T& def){
    switch (msg){
        case Msg::Get:
        case Msg::GetCurrent:
        case Msg::GetDefault:
        case Msg::Reset:
            data = Capability::createOneValue(data.type(), def);
            return {};

        case Msg::Set:
            return data.currentItem<T>() == def ?
                Result() : Result(ReturnCode::Failure, ConditionCode::BadValue);

        default:
            return {ReturnCode::Failure, ConditionCode::CapBadOperation};
    }
}


template<typename T>
static Result enmGetSetConst(Msg msg, Capability& data, const T& def){
    switch (msg){
        case Msg::Get:
            data = Capability::createEnumeration(data.type(), {def});
            return {};

        case Msg::GetCurrent:
        case Msg::GetDefault:
        case Msg::Reset:
            data = Capability::createOneValue(data.type(), def);
            return {};

        case Msg::Set:
            return data.currentItem<T>() == def ?
                Result() : Result(ReturnCode::Failure, ConditionCode::BadValue);

        default:
            return {ReturnCode::Failure, ConditionCode::CapBadOperation};
    }
}

Result SimpleDs::capCommon(const Identity&, Msg msg, Capability& data){
    auto it = m_caps.find(data.type());
    if (it != m_caps.end()){
        return (it->second)(msg, data);
    }

    return capUnsupported();
}

Result SimpleDs::capabilityGet(const Identity& origin, Capability& data){
    return capCommon(origin, Msg::Get, data);
}

Result SimpleDs::capabilityGetCurrent(const Identity& origin, Capability& data){
    return capCommon(origin, Msg::GetCurrent, data);
}

Result SimpleDs::capabilityGetDefault(const Identity& origin, Capability& data){
    return capCommon(origin, Msg::GetDefault, data);
}

Result SimpleDs::capabilityQuerySupport(const Identity&, Capability& data){
    auto it = m_query.find(data.type());
    MsgSupport sup = it != m_query.end() ? it->second : msgSupportEmpty;
    data = Capability::createOneValue(data.type(), sup);
    return success();
}

Result SimpleDs::capabilityReset(const Identity& origin, Capability& data){
    return capCommon(origin, Msg::Reset, data);
}

Result SimpleDs::capabilityResetAll(const Identity& origin){
    for (auto& pair : m_query){
        if ((pair.second & MsgSupport::Reset) != msgSupportEmpty){
            Capability dummyCap(pair.first);
            capCommon(origin, Msg::Reset, dummyCap);
        }
    }

    return success();
}

Result SimpleDs::capabilitySet(const Identity& origin, Capability& data){
    return capCommon(origin, Msg::Set, data);
}

Result SimpleDs::eventProcess(const Identity&, Event& event){
    // Qt needs to process its events, otherwise the GUI will appear frozen
    // this is Windows-only method, Linux and macOS behave differently
    if (static_cast<bool>(application)){
        QApplication::processEvents();
        QApplication::sendPostedEvents();
    }

    event.setMessage(Msg::Null);
    return {ReturnCode::NotDsEvent, ConditionCode::Success};
}

Result SimpleDs::identityOpenDs(const Identity&){
    if (bmpData.isEmpty()){
        // init the image data
        QResource res(QStringLiteral("/image.bmp"));
        bmpData = qUncompress(res.data(), static_cast<int>(res.size()));
        if (bmpData.isEmpty()){
            return {ReturnCode::Failure, ConditionCode::LowMemory};
        }
    }

    // init caps
    // there are caps a minimal source must support
    // query -> says which operations a cap supports
    // caps  -> has handler for each specific cap
    m_query[CapType::SupportedCaps] = msgSupportGetAll;
    m_caps[CapType::SupportedCaps] = [this](Msg msg, Capability& data){
        switch (msg){
            case Msg::Get:
            case Msg::GetCurrent:
            case Msg::GetDefault: {
                data = Capability::createArray<CapType::SupportedCaps>(m_caps.size());
                auto arr = data.array<CapType::SupportedCaps>();
                UInt32 i = 0;
                for (const auto& kv : m_caps){
                    arr[i] = kv.first;
                    i++;
                }

                return success();
            }

            default:
                return capBadOperation();
        }
    };

    m_query[CapType::UiControllable] = msgSupportGetAll;
    m_caps[CapType::UiControllable] = std::bind(enmGet<Bool>, _1, _2, Bool(true));

    m_query[CapType::DeviceOnline] = msgSupportGetAll;
    m_caps[CapType::DeviceOnline] = std::bind(enmGet<Bool>, _1, _2, Bool(true));

    m_query[CapType::XferCount] = msgSupportGetAllSetReset;
    m_caps[CapType::XferCount] = [this](Msg msg, Capability& data) -> Result{
        if (msg == Msg::Set){
            auto item = data.currentItem<Int16>();
            if (item > 1 || item < -1){
                return badValue();
            }
        }

        auto ret = oneValGetSet<Int16>(msg, data, m_capXferCount, -1);
        if (Twpp::success(ret) && m_capXferCount == 0){
            m_capXferCount = -1;
            return {ReturnCode::CheckStatus, ConditionCode::BadValue};
        }

        return ret;
    };

    m_query[CapType::ICompression] = msgSupportGetAllSetReset;
    m_caps[CapType::ICompression] = std::bind(enmGetSetConst<Compression>, _1, _2, Compression::None);


    m_query[CapType::IBitDepth] = msgSupportGetAllSetReset;
    m_caps[CapType::IBitDepth] = std::bind(enmGetSetConst<UInt16>, _1, _2, UInt16(header()->biBitCount));

    m_query[CapType::IBitOrder] = msgSupportGetAllSetReset;
    m_caps[CapType::IBitOrder] = std::bind(enmGetSetConst<BitOrder>, _1, _2, BitOrder::MsbFirst);

    m_query[CapType::IPlanarChunky] = msgSupportGetAllSetReset;
    m_caps[CapType::IPlanarChunky] = std::bind(enmGetSetConst<PlanarChunky>, _1, _2, PlanarChunky::Chunky);

    m_query[CapType::IPhysicalWidth] = msgSupportGetAll;
    m_caps[CapType::IPhysicalWidth] = std::bind(oneValGet<Fix32>, _1, _2, Fix32(static_cast<float>(header()->biWidth) / RESOLUTION));

    m_query[CapType::IPhysicalHeight] = msgSupportGetAll;
    m_caps[CapType::IPhysicalHeight] = std::bind(oneValGet<Fix32>, _1, _2, Fix32(static_cast<float>(header()->biHeight) / RESOLUTION));

    m_query[CapType::IPixelFlavor] = msgSupportGetAllSetReset;
    m_caps[CapType::IPixelFlavor] = std::bind(enmGetSetConst<PixelFlavor>, _1, _2, PixelFlavor::Chocolate);

    m_query[CapType::IPixelType] = msgSupportGetAllSetReset;
    m_caps[CapType::IPixelType] = std::bind(enmGetSetConst<PixelType>, _1, _2, PixelType::Rgb);

    m_query[CapType::IUnits] = msgSupportGetAllSetReset;
    m_caps[CapType::IUnits] = std::bind(enmGetSetConst<Unit>, _1, _2, Unit::Inches);

    m_query[CapType::IXferMech] = msgSupportGetAllSetReset;
    m_caps[CapType::IXferMech] = [this](Msg msg, Capability& data) -> Result{
        switch (msg){
            case Msg::Get:
                data = Capability::createEnumeration<CapType::IXferMech>(
                    {XferMech::Native, XferMech::Memory}, m_capXferMech == XferMech::Native ? 0 : 1, 0);
                return success();

            case Msg::Reset:
                m_capXferMech = XferMech::Native;
                // fallthrough
            case Msg::GetCurrent:
                data = Capability::createOneValue<CapType::IXferMech>(m_capXferMech);
                return success();

            case Msg::GetDefault:
                data = Capability::createOneValue<CapType::IXferMech>(XferMech::Native);
                return success();

            case Msg::Set: {
                auto mech = data.currentItem<CapType::IXferMech>();
                if (mech == XferMech::Native || mech == XferMech::Memory){
                    m_capXferMech = mech;
                    return success();
                } else {
                    return badValue();
                }
            }

            default:
                return capBadOperation();
        }
    };

    m_query[CapType::IXResolution] = msgSupportGetAllSetReset;
    m_caps[CapType::IXResolution] = [](Msg msg, Capability& data){
        switch (msg){
            case Msg::Get:
                data = Capability::createEnumeration(data.type(), {Fix32(RESOLUTION)});
                return success();
            case Msg::GetCurrent:
            case Msg::GetDefault:
            case Msg::Reset:
                data = Capability::createOneValue(data.type(), Fix32(RESOLUTION));
                return success();

            case Msg::Set:
                return data.currentItem<Fix32>() == RESOLUTION ?
                    success() : badValue();

            default:
                return capBadOperation();
        }
    };

    m_query[CapType::IYResolution] = msgSupportGetAllSetReset;
    m_caps[CapType::IYResolution] = m_caps[CapType::IXResolution];

    m_query[CapType::IXNativeResolution] = msgSupportGetAll;
    m_caps[CapType::IXNativeResolution] = std::bind(enmGet<Fix32>, _1, _2, Fix32(RESOLUTION));

    m_query[CapType::IYNativeResolution] = msgSupportGetAll;
    m_caps[CapType::IYNativeResolution] = m_caps[CapType::IXNativeResolution];

    return success();
}

Result SimpleDs::identityCloseDs(const Identity&){
    // no need to explicitly release any resources if using RAII
    // TWPP will free the whole source on its own after this method
    return success();
}

Result SimpleDs::pendingXfersGet(const Identity&, PendingXfers& data){
    data.setCount(m_pendingXfers);
    return success();
}

Result SimpleDs::pendingXfersEnd(const Identity&, PendingXfers& data){
    data.setCount(0);
    return success();
}

Result SimpleDs::pendingXfersReset(const Identity&, PendingXfers& data){
    data.setCount(0);
    return success();
}

Result SimpleDs::setupMemXferGet(const Identity&, SetupMemXfer& data){
    auto bpl = bytesPerLine();
    auto max = bpl * static_cast<UInt32>(header()->biHeight);

    data.setMinSize(bpl);
    data.setPreferredSize(max);
    data.setMaxSize(max);
    return success();
}

Result SimpleDs::userInterfaceDisable(const Identity&, UserInterface&){
    scanDialog.reset();

#if TWPP_DETAIL_OS_WIN
    guiBridge.reset();
#endif

    application.reset();
    return success();
}

Result SimpleDs::userInterfaceEnable(const Identity&, UserInterface& ui){
    m_pendingXfers = 1;
    m_memXferYOff = 0;

    application = std::unique_ptr<QApplication>(new QApplication(argc, argv));
    QWidget* parent = nullptr;

#if TWPP_DETAIL_OS_WIN
    // we use Qt, some Windows-Qt glue is necessary to set the parent window of our dialog
    if (ui.parent()){
        guiBridge = std::unique_ptr<QWidget>(new QWidget);

        HWND appWindow = static_cast<HWND>(ui.parent().raw());
        HWND bridgeWindow = reinterpret_cast<HWND>(guiBridge->winId());
        long bridgeFlags = GetWindowLong(bridgeWindow, GWL_STYLE);
        SetWindowLong(bridgeWindow, GWL_STYLE, bridgeFlags | WS_CHILD);
        SetParent(bridgeWindow, appWindow);

        if (ui.modalUi()){
            long appFlags = GetWindowLong(appWindow, GWL_STYLE);
            SetWindowLong(appWindow, GWL_STYLE, appFlags | WS_DISABLED);
        }
    }

    parent = guiBridge.get();
#endif

    // the dialog does not need to know about TWPP, just give it simple functions to notify us
    auto scanFunction = [this](){
        notifyXferReady();
    };

    auto cancelFunction = [this](){
        notifyCloseCancel();
    };

    TwGlue glue = {scanFunction, cancelFunction};
    scanDialog = std::unique_ptr<ScanDialog>(new ScanDialog(parent, glue));
    scanDialog->show();

    return success();
}

Result SimpleDs::userInterfaceEnableUiOnly(const Identity&, UserInterface&){
    // as a minimal source, we do not support GUI that just saves settings
    return {ReturnCode::Failure, ConditionCode::OperationError};
}

Result SimpleDs::imageInfoGet(const Identity&, ImageInfo& data){
    // our image does not change
    auto dib = header();
    data.setBitsPerPixel(static_cast<Int16>(dib->biBitCount));
    data.setHeight(dib->biHeight);
    data.setPixelType(PixelType::Rgb);
    data.setPlanar(false);
    data.setWidth(dib->biWidth);
    data.setXResolution(RESOLUTION);
    data.setYResolution(RESOLUTION);

    data.setSamplesPerPixel(3);
    data.bitsPerSample()[0] = 8;
    data.bitsPerSample()[1] = 8;
    data.bitsPerSample()[2] = 8;

    return success();
}

Result SimpleDs::imageLayoutGet(const Identity&, ImageLayout& data){
    // our image does not change
    auto dib = header();

    data.setDocumentNumber(1);
    data.setFrameNumber(1);
    data.setPageNumber(1);
    data.setFrame(Frame(0, 0, static_cast<float>(dib->biWidth) / RESOLUTION, static_cast<float>(dib->biHeight) / RESOLUTION));
    return success();
}

Result SimpleDs::imageLayoutGetDefault(const Identity& origin, ImageLayout& data){
    return imageLayoutGet(origin, data);
}

Result SimpleDs::imageLayoutSet(const Identity& origin, ImageLayout& lay){
    // we dont support setting image frame

    ImageLayout def;
    imageLayoutGetDefault(origin, def);

    return lay.frame() == def.frame() ? success() : badValue();
}

Result SimpleDs::imageLayoutReset(const Identity& origin, ImageLayout& data){
    return imageLayoutGet(origin, data);
}

Result SimpleDs::imageMemXferGet(const Identity& origin, ImageMemXfer& data){
    if (!m_pendingXfers){
        return seqError();
    }

    // we can call our TWPP methods, but be careful about states
    SetupMemXfer setup;
    setupMemXferGet(origin, setup);

    // just a simple stored BMP image
    auto dib = header();
    auto bpl = bytesPerLine();
    auto memSize = data.memory().size();
    if (memSize > setup.maxSize() || memSize < setup.minSize()){
        return badValue();
    }

    auto maxRows = memSize / bpl;
    auto rows = std::min<UInt32>(maxRows, static_cast<UInt32>(dib->biHeight) - m_memXferYOff);
    if (rows == 0){
        return seqError(); // image already transfered in this session
    }

    data.setBytesPerRow(bpl);
    data.setColumns(static_cast<UInt32>(dib->biWidth));
    data.setRows(rows);
    data.setBytesWritten(rows * bpl);
    data.setXOffset(0);
    data.setYOffset(m_memXferYOff);
    data.setCompression(Compression::None);

    auto lock = data.memory().data();
    char* out = lock.data();

    // bottom-up BMP -> top-down memory transfer
    auto begin = bmpEnd() - (bpl * (m_memXferYOff + 1));
    for (UInt32 i = 0; i < rows; i++){
        // copy bytes
        std::copy(begin, begin + bpl, out);

        char* line = out;
        out += bpl;
        begin -= bpl;

        // BGR BMP -> RGB memory transfer
        for ( ; line + 3 < out; line += 3){
            std::swap(line[0], line[2]);
        }
    }

    m_memXferYOff += rows;

    if (m_memXferYOff >= static_cast<UInt32>(std::abs(dib->biHeight))){
        m_pendingXfers = 0;
        return {ReturnCode::XferDone, ConditionCode::Success};
    }

    return success();
}

Result SimpleDs::imageNativeXferGet(const Identity&, ImageNativeXfer& data){
    if (!m_pendingXfers){
        return seqError();
    }

    // it does not get easier than that if we already have BMP
    data = ImageNativeXfer(bmpSize());

    std::copy(bmpBegin(), bmpEnd(), data.data<char>().data());

    m_pendingXfers = 0;
    return {ReturnCode::XferDone, ConditionCode::Success};
}

const BITMAPINFOHEADER* SimpleDs::header() const noexcept{
    return reinterpret_cast<const BITMAPINFOHEADER*>(bmpData.data() + sizeof(BITMAPFILEHEADER));
}

UInt32 SimpleDs::bytesPerLine() const noexcept{
    auto dib = header();
    return static_cast<UInt32>(dib->biWidth * dib->biBitCount + 31) / 32 * 4;
}

UInt32 SimpleDs::bmpSize() const noexcept{
    return static_cast<UInt32>(bmpData.size()) - sizeof(BITMAPFILEHEADER);
}

const char* SimpleDs::bmpBegin() const noexcept{
    return bmpData.cbegin() + sizeof(BITMAPFILEHEADER);
}

const char* SimpleDs::bmpEnd() const noexcept{
    return bmpData.cend();
}

#if TWPP_DETAIL_OS_WIN
BOOL WINAPI DllMain(HINSTANCE, DWORD reason, LPVOID){
    switch (reason){
        case DLL_PROCESS_ATTACH:
            // anything you want to execute when the source is loaded
            break;


        case DLL_PROCESS_DETACH:
            // anything you want to execute when the source is unloaded
            break;
    }

    return true;
}
#endif
