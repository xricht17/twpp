/*

The MIT License (MIT)

Copyright (c) 2015 Martin Richter

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#ifndef TWPP_DETAIL_FILE_CAPABILITY_HPP
#define TWPP_DETAIL_FILE_CAPABILITY_HPP

#include "../twpp.hpp"

namespace Twpp {

namespace Detail {

/// Mapping of capability type to type identifier and data type.
template<CapType cap> struct Cap {};
template<> struct Cap<CapType::Alarms> {static constexpr const Type twty = Type::UInt16; typedef Alarm DataType;};
template<> struct Cap<CapType::AlarmVolume> {static constexpr const Type twty = Type::Int32; typedef Int32 DataType;};
template<> struct Cap<CapType::Author> {static constexpr const Type twty = Type::Str128; typedef Str128 DataType;};
template<> struct Cap<CapType::AutoFeed> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::AutomaticCapture> {static constexpr const Type twty = Type::Int32; typedef Int32 DataType;};
template<> struct Cap<CapType::AutomaticSenseMedium> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::AutoScan> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::AXferMech> {static constexpr const Type twty = Type::UInt16; typedef XferMech DataType;};
template<> struct Cap<CapType::BatteryMinutes> {static constexpr const Type twty = Type::Int32; typedef Int32 DataType;};
template<> struct Cap<CapType::BatteryPercentage> {static constexpr const Type twty = Type::Int16; typedef Int16 DataType;};
template<> struct Cap<CapType::CameraEnabled> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::CameraOrder> {static constexpr const Type twty = Type::UInt16; typedef PixelType DataType;};
template<> struct Cap<CapType::CameraPreviewUi> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::CameraSide> {static constexpr const Type twty = Type::UInt16; typedef CameraSide DataType;};
template<> struct Cap<CapType::Caption> {static constexpr const Type twty = Type::Str255; typedef Str255 DataType;};
template<> struct Cap<CapType::ClearBuffers> {static constexpr const Type twty = Type::UInt16; typedef ClearBuffers DataType;};
template<> struct Cap<CapType::ClearPage> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::CustomDsData> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::CustomInterfaceGuid> {static constexpr const Type twty = Type::Str255; typedef Str255 DataType;};
template<> struct Cap<CapType::DeviceEvent> {static constexpr const Type twty = Type::UInt16; typedef DeviceEvent::Type DataType;}; // Capability->UInt16, DeviceEvent->UInt32
template<> struct Cap<CapType::DeviceOnline> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::DeviceTimeDate> {static constexpr const Type twty = Type::Str32; typedef Str32 DataType;};
template<> struct Cap<CapType::DoubleFeedDetection> {static constexpr const Type twty = Type::UInt16; typedef DoubleFeedDetection DataType;};
template<> struct Cap<CapType::DoubleFeedDetectionLength> {static constexpr const Type twty = Type::Fix32; typedef Fix32 DataType;};
template<> struct Cap<CapType::DoubleFeedDetectionResponse> {static constexpr const Type twty = Type::UInt16; typedef DoubleFeedResponse DataType;};
template<> struct Cap<CapType::DoubleFeedDetectionSensitivity> {static constexpr const Type twty = Type::UInt16; typedef DoubleFeedSensitivity DataType;};
template<> struct Cap<CapType::Duplex> {static constexpr const Type twty = Type::UInt16; typedef Duplex DataType;};
template<> struct Cap<CapType::DuplexEnabled> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::EnableDsUiOnly> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::Endorser> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Cap<CapType::ExtendedCaps> {static constexpr const Type twty = Type::UInt16; typedef CapType DataType;};
template<> struct Cap<CapType::FeederAlignment> {static constexpr const Type twty = Type::UInt16; typedef FeederAlignment DataType;};
template<> struct Cap<CapType::FeederEnabled> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::FeederLoaded> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::FeederOrder> {static constexpr const Type twty = Type::UInt16; typedef FeederOrder DataType;};
template<> struct Cap<CapType::FeederPocket> {static constexpr const Type twty = Type::UInt16; typedef FeederPocket DataType;};
template<> struct Cap<CapType::FeederPrep> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::FeedPage> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::IAutoBright> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::IAutoDiscardBlankPages> {static constexpr const Type twty = Type::Int32; typedef DiscardBlankPages DataType;};
template<> struct Cap<CapType::IAutomaticBorderDetection> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::IAutomaticColorEnabled> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::IAutomaticColorNonColorPixelType> {static constexpr const Type twty = Type::UInt16; typedef PixelType DataType;}; // only BW/Gray
template<> struct Cap<CapType::IAutomaticCropUsesFrame> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::IAutomaticDeskew> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::IAutomaticLengthDetection> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::IAutomaticRotate> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::IAutoSize> {static constexpr const Type twty = Type::UInt16; typedef AutoSize DataType;};
template<> struct Cap<CapType::IBarCodeDetectionEnabled> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::IBarCodeMaxRetries> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Cap<CapType::IBarCodeMaxSearchPriorities> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Cap<CapType::IBarCodeSearchMode> {static constexpr const Type twty = Type::UInt16; typedef SearchMode DataType;};
template<> struct Cap<CapType::IBarCodeSearchPriorities> {static constexpr const Type twty = Type::UInt16; typedef BarCodeType DataType;};
template<> struct Cap<CapType::IBarCodeTimeOut> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Cap<CapType::IBitDepth> {static constexpr const Type twty = Type::UInt16; typedef UInt16 DataType;};
template<> struct Cap<CapType::IBitDepthReduction> {static constexpr const Type twty = Type::UInt16; typedef BitDepthReduction DataType;};
template<> struct Cap<CapType::IBitOrder> {static constexpr const Type twty = Type::UInt16; typedef BitOrder DataType;};
template<> struct Cap<CapType::IBitOrderCodes> {static constexpr const Type twty = Type::UInt16; typedef BitOrder DataType;};
template<> struct Cap<CapType::IBrightness> {static constexpr const Type twty = Type::Fix32; typedef Fix32 DataType;};
template<> struct Cap<CapType::ICcittKFactor> {static constexpr const Type twty = Type::UInt16; typedef UInt16 DataType;};
template<> struct Cap<CapType::IColorManagementEnabled> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::ICompression> {static constexpr const Type twty = Type::UInt16; typedef Compression DataType;};
template<> struct Cap<CapType::IContrast> {static constexpr const Type twty = Type::Fix32; typedef Fix32 DataType;};
template<> struct Cap<CapType::ICustHalfTone> {static constexpr const Type twty = Type::UInt8; typedef UInt8 DataType;};
template<> struct Cap<CapType::IExposureTime> {static constexpr const Type twty = Type::Fix32; typedef Fix32 DataType;};
template<> struct Cap<CapType::IExtImageInfo> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::IFeederType> {static constexpr const Type twty = Type::UInt16; typedef FeederType DataType;};
template<> struct Cap<CapType::IFilmType> {static constexpr const Type twty = Type::UInt16; typedef FilmType DataType;};
template<> struct Cap<CapType::IFilter> {static constexpr const Type twty = Type::UInt16; typedef Filter DataType;};
template<> struct Cap<CapType::IFlashUsed> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::IFlashUsed2> {static constexpr const Type twty = Type::UInt16; typedef Flash DataType;}; // Capability->UInt16, DeviceEvent->UInt32
template<> struct Cap<CapType::IFlipRotation> {static constexpr const Type twty = Type::UInt16; typedef FlipRotation DataType;};
template<> struct Cap<CapType::IFrames> {static constexpr const Type twty = Type::Frame; typedef Frame DataType;};
template<> struct Cap<CapType::IGamma> {static constexpr const Type twty = Type::Fix32; typedef Fix32 DataType;};
template<> struct Cap<CapType::IHalfTones> {static constexpr const Type twty = Type::Str32; typedef Str32 DataType;};
template<> struct Cap<CapType::IHighLight> {static constexpr const Type twty = Type::Fix32; typedef Fix32 DataType;};
template<> struct Cap<CapType::IIccProfile> {static constexpr const Type twty = Type::UInt16; typedef IccProfile DataType;};
template<> struct Cap<CapType::IImageDataSet> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Cap<CapType::IImageFileFormat> {static constexpr const Type twty = Type::UInt16; typedef ImageFileFormat DataType;};
template<> struct Cap<CapType::IImageFilter> {static constexpr const Type twty = Type::UInt16; typedef ImageFilter DataType;};
template<> struct Cap<CapType::IImageMerge> {static constexpr const Type twty = Type::UInt16; typedef ImageMerge DataType;};
template<> struct Cap<CapType::IImageMergeHeightThreshold> {static constexpr const Type twty = Type::Fix32; typedef Fix32 DataType;};
template<> struct Cap<CapType::IJpegPixelType> {static constexpr const Type twty = Type::UInt16; typedef PixelType DataType;};
template<> struct Cap<CapType::IJpegQuality> {static constexpr const Type twty = Type::Int16; typedef JpegQuality DataType;};  // JpegQuality or 0-100
template<> struct Cap<CapType::IJpegSubSampling> {static constexpr const Type twty = Type::UInt16; typedef JpegSubSampling DataType;};
template<> struct Cap<CapType::ILampState> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::ILightPath> {static constexpr const Type twty = Type::UInt16; typedef LightPath DataType;};
template<> struct Cap<CapType::ILightSource> {static constexpr const Type twty = Type::UInt16; typedef LightSource DataType;};
template<> struct Cap<CapType::IMaxFrames> {static constexpr const Type twty = Type::UInt16; typedef UInt16 DataType;};
template<> struct Cap<CapType::IMinimumHeight> {static constexpr const Type twty = Type::Fix32; typedef Fix32 DataType;};
template<> struct Cap<CapType::IMinimumWidth> {static constexpr const Type twty = Type::Fix32; typedef Fix32 DataType;};
template<> struct Cap<CapType::IMirror> {static constexpr const Type twty = Type::UInt16; typedef Mirror DataType;};
template<> struct Cap<CapType::Indicators> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::IndicatorsMode> {static constexpr const Type twty = Type::UInt16; typedef IndicatorsMode DataType;};
template<> struct Cap<CapType::INoiseFilter> {static constexpr const Type twty = Type::UInt16; typedef NoiseFilter DataType;};
template<> struct Cap<CapType::IOrientation> {static constexpr const Type twty = Type::UInt16; typedef Orientation DataType;};
template<> struct Cap<CapType::IOverScan> {static constexpr const Type twty = Type::UInt16; typedef OverScan DataType;};
template<> struct Cap<CapType::IPatchCodeDetectionEnabled> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::IPatchCodeMaxRetries> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Cap<CapType::IPatchCodeMaxSearchPriorities> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Cap<CapType::IPatchCodeSearchMode> {static constexpr const Type twty = Type::UInt16; typedef SearchMode DataType;};
template<> struct Cap<CapType::IPatchCodeSearchPriorities> {static constexpr const Type twty = Type::UInt16; typedef PatchCode DataType;};
template<> struct Cap<CapType::IPatchCodeTimeOut> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Cap<CapType::IPhysicalHeight> {static constexpr const Type twty = Type::Fix32; typedef Fix32 DataType;};
template<> struct Cap<CapType::IPhysicalWidth> {static constexpr const Type twty = Type::Fix32; typedef Fix32 DataType;};
template<> struct Cap<CapType::IPixelFlavor> {static constexpr const Type twty = Type::UInt16; typedef PixelFlavor DataType;};
template<> struct Cap<CapType::IPixelFlavorCodes> {static constexpr const Type twty = Type::UInt16; typedef PixelFlavor DataType;};
template<> struct Cap<CapType::IPixelType> {static constexpr const Type twty = Type::UInt16; typedef PixelType DataType;};
template<> struct Cap<CapType::IPlanarChunky> {static constexpr const Type twty = Type::UInt16; typedef ColorFormat DataType;};
template<> struct Cap<CapType::IRotation> {static constexpr const Type twty = Type::Fix32; typedef Fix32 DataType;};
template<> struct Cap<CapType::IShadow> {static constexpr const Type twty = Type::Fix32; typedef Fix32 DataType;};
template<> struct Cap<CapType::ISupportedBarCodeTypes> {static constexpr const Type twty = Type::UInt16; typedef BarCodeType DataType;};
template<> struct Cap<CapType::ISupportedExtImageInfo> {static constexpr const Type twty = Type::UInt16; typedef Twpp::InfoId DataType;};
template<> struct Cap<CapType::ISupportedPatchCodeTypes> {static constexpr const Type twty = Type::UInt16; typedef PatchCode DataType;};
template<> struct Cap<CapType::ISupportedSizes> {static constexpr const Type twty = Type::UInt16; typedef PaperSize DataType;};
template<> struct Cap<CapType::IThreshold> {static constexpr const Type twty = Type::Fix32; typedef Fix32 DataType;};
template<> struct Cap<CapType::ITiles> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::ITimeFill> {static constexpr const Type twty = Type::UInt16; typedef UInt16 DataType;};
template<> struct Cap<CapType::IUndefinedImageSize> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::IUnits> {static constexpr const Type twty = Type::UInt16; typedef Unit DataType;};
template<> struct Cap<CapType::IXferMech> {static constexpr const Type twty = Type::UInt16; typedef XferMech DataType;};
template<> struct Cap<CapType::IXNativeResolution> {static constexpr const Type twty = Type::Fix32; typedef Fix32 DataType;};
template<> struct Cap<CapType::IXResolution> {static constexpr const Type twty = Type::Fix32; typedef Fix32 DataType;};
template<> struct Cap<CapType::IXScaling> {static constexpr const Type twty = Type::Fix32; typedef Fix32 DataType;};
template<> struct Cap<CapType::IYNativeResolution> {static constexpr const Type twty = Type::Fix32; typedef Fix32 DataType;};
template<> struct Cap<CapType::IYResolution> {static constexpr const Type twty = Type::Fix32; typedef Fix32 DataType;};
template<> struct Cap<CapType::IYScaling> {static constexpr const Type twty = Type::Fix32; typedef Fix32 DataType;};
template<> struct Cap<CapType::IZoomFactor> {static constexpr const Type twty = Type::Int16; typedef Int16 DataType;};
template<> struct Cap<CapType::JobControl> {static constexpr const Type twty = Type::UInt16; typedef JobControl DataType;};
template<> struct Cap<CapType::Language> {static constexpr const Type twty = Type::UInt16; typedef Language DataType;};
template<> struct Cap<CapType::MaxBatchBuffers> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Cap<CapType::MicrEnabled> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::PaperDetectable> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::PaperHandling> {static constexpr const Type twty = Type::UInt16; typedef PaperHandling DataType;};
template<> struct Cap<CapType::PowerSaveTime> {static constexpr const Type twty = Type::Int32; typedef Int32 DataType;};
template<> struct Cap<CapType::PowerSupply> {static constexpr const Type twty = Type::UInt16; typedef PowerSupply DataType;}; // Capability->UInt16, DeviceEvent->Int32
template<> struct Cap<CapType::Printer> {static constexpr const Type twty = Type::UInt16; typedef Printer DataType;};
template<> struct Cap<CapType::PrinterEnabled> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::PrinterFontStyle> {static constexpr const Type twty = Type::UInt16; typedef FontStyle DataType;};
template<> struct Cap<CapType::PrinterCharRotation> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Cap<CapType::PrinterIndex> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Cap<CapType::PrinterIndexLeadChar> {static constexpr const Type twty = Type::Str32; typedef Str32 DataType;};
template<> struct Cap<CapType::PrinterIndexMaxValue> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Cap<CapType::PrinterIndexNumDigits> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Cap<CapType::PrinterIndexStep> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Cap<CapType::PrinterIndexTrigger> {static constexpr const Type twty = Type::UInt16; typedef IndexTrigger DataType;};
template<> struct Cap<CapType::PrinterMode> {static constexpr const Type twty = Type::UInt16; typedef PrinterMode DataType;};
template<> struct Cap<CapType::PrinterString> {static constexpr const Type twty = Type::Str255; typedef Str255 DataType;};
template<> struct Cap<CapType::PrinterStringPreview> {static constexpr const Type twty = Type::Str255; typedef Str255 DataType;};
template<> struct Cap<CapType::PrinterSuffix> {static constexpr const Type twty = Type::Str255; typedef Str255 DataType;};
template<> struct Cap<CapType::PrinterVerticalOffset> {static constexpr const Type twty = Type::Fix32; typedef Fix32 DataType;};
template<> struct Cap<CapType::ReacquireAllowed> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::RewindPage> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::Segmented> {static constexpr const Type twty = Type::UInt16; typedef Segmented DataType;};
template<> struct Cap<CapType::SerialNumber> {static constexpr const Type twty = Type::Str255; typedef Str255 DataType;};
template<> struct Cap<CapType::SupportedCaps> {static constexpr const Type twty = Type::UInt16; typedef CapType DataType;};
template<> struct Cap<CapType::SupportedCapsSegmentUnique> {static constexpr const Type twty = Type::UInt16; typedef CapType DataType;};
template<> struct Cap<CapType::SupportedDats> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Cap<CapType::ThumbnailsEnabled> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::TimeBeforeFirstCapture> {static constexpr const Type twty = Type::Int32; typedef Int32 DataType;};
template<> struct Cap<CapType::TimeBetweenCaptures> {static constexpr const Type twty = Type::Int32; typedef Int32 DataType;};
template<> struct Cap<CapType::TimeDate> {static constexpr const Type twty = Type::Str32; typedef Str32 DataType;};
template<> struct Cap<CapType::UiControllable> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Cap<CapType::XferCount> {static constexpr const Type twty = Type::Int16; typedef Int16 DataType;};

TWPP_DETAIL_PACK_BEGIN
// certain apps assume that size of OneValue item is always at least 4 bytes
// add padding that extends the sign of signed integers
// and pads with zeroes for unsigned integers
// all other cases use their data types directly
template<typename DataType, bool isSmall, bool/* isSigned*/> // false, any
struct OneValueProxy {
    OneValueProxy& operator=(const DataType& value) noexcept{
        m_data = value;
        return *this;
    }

    operator const DataType&() const noexcept{
        return m_data;
    }

    operator DataType&() noexcept{
        return m_data;
    }

    DataType m_data;
};

template<typename DataType>
struct OneValueProxy<DataType, true, true> {
    OneValueProxy& operator=(DataType value) noexcept{
        m_signed = static_cast<Int32>(value);
        return *this;
    }

    operator DataType() const noexcept{
        return m_data;
    }

    operator DataType&() noexcept{
        return m_data;
    }

    union {
        DataType m_data;
        Int32 m_signed;
    };
};

template<typename DataType>
struct OneValueProxy<DataType, true, false> {
    OneValueProxy& operator=(DataType value) noexcept{
        m_unsigned = static_cast<UInt32>(value);
        return *this;
    }

    operator DataType() const noexcept{
        return m_data;
    }

    operator DataType&() noexcept{
        return m_data;
    }

    union {
        DataType m_data;
        UInt32 m_unsigned;
    };
};

template<typename DataType>
struct OneValueData {
    Type m_itemType;
    OneValueProxy<DataType, sizeof(DataType) < sizeof(UInt32), std::is_signed<DataType>::value> m_item;
};

template<typename DataType>
struct ArrayData {
    Type m_itemType;
    UInt32 m_numItems;
    DataType m_items[1];
};

template<typename DataType>
struct EnumerationData {
    Type m_itemType;
    UInt32 m_numItems;
    UInt32 m_currIndex;
    UInt32 m_defIndex;
    DataType m_items[1];
};

// Range items are always 4 bytes large,
// add padding for smaller data types
template<typename DataType>
struct RangeProxy {
    typedef typename std::conditional<
        std::is_signed<DataType>::value, Int32, UInt32
    >::type InnerType;

    RangeProxy& operator=(DataType value) noexcept{
        m_data = value;
        return *this;
    }

    operator DataType() const noexcept{
        return static_cast<DataType>(m_data);
    }

    operator DataType&() noexcept{
        return *alias_cast<DataType*>(&m_data);
    }

    InnerType m_data;
};

template<>
struct RangeProxy<Fix32> {
    RangeProxy& operator=(Fix32 value) noexcept{
        m_data = value;
        return *this;
    }

    operator Fix32() const noexcept{
        return m_data;
    }

    operator Fix32&() noexcept{
        return m_data;
    }

    Fix32 m_data;
};

template<typename DataType>
struct RangeData {
    Type m_itemType;
    RangeProxy<DataType> m_minValue;
    RangeProxy<DataType> m_maxValue;
    RangeProxy<DataType> m_stepSize;
    RangeProxy<DataType> m_defValue;
    RangeProxy<DataType> m_currValue;
};
TWPP_DETAIL_PACK_END


template<typename DataType>
struct IsNumeric {
    static constexpr bool value = std::is_integral<DataType>::value || std::is_same<DataType, Fix32>::value;
};

}

class Capability;

/// Capability container holding a single value.
/// \tparam twty ID of the internal data type.
/// \tparam DataType Exported data type.
template<Type twty, typename DataType = typename Detail::Twty<twty>::Type>
class OneValue {

    friend class Capability;

public:
    static constexpr const ConType contype = ConType::OneValue;
    typedef DataType* iterator;
    typedef const DataType* const_iterator;

    /// Creates an invalid container.
    constexpr OneValue() noexcept{}

    /// ID of the internal data type.
    Type type() const noexcept{
        return m_data->m_itemType;
    }

    /// The contained value.
    DataType& item() noexcept{
        return m_data->m_item;
    }

    /// The contained value.
    const DataType& item() const noexcept{
        return m_data->m_item;
    }

    /// Sets the contained value.
    void setItem(const DataType& item) noexcept{
        m_data->m_item = item;
    }

    operator bool() const noexcept{
        return m_data;
    }


    iterator begin() noexcept{
        return &m_data->m_item;
    }

    const_iterator begin() const noexcept{
        return cbegin();
    }

    const_iterator cbegin() const noexcept{
        return &m_data->m_item;
    }

    iterator end() noexcept{
        return &m_data->m_item + 1;
    }

    const_iterator end() const noexcept{
        return cend();
    }

    const_iterator cend() const noexcept{
        return &m_data->m_item + 1;
    }

private:
    OneValue(Handle h) : m_data(h){}

    Detail::Lock<Detail::OneValueData<DataType> > m_data;

};

// disable OneValue for incompatible types
template<typename DataType>
class OneValue<Type::DontCare, DataType>;
template<typename DataType>
class OneValue<Type::Handle, DataType>;


/// Capability container holding an array of values.
/// \tparam twty ID of the internal data type.
/// \tparam DataType Exported data type.
template<Type twty, typename DataType = typename Detail::Twty<twty>::Type>
class Array {

    friend class Capability;

public:
    static constexpr const ConType contype = ConType::Array;
    typedef DataType* iterator;
    typedef const DataType* const_iterator;

    /// Creates an invalid container.
    constexpr Array() noexcept{}

    /// ID of the internal data type.
    Type type() const noexcept{
        return m_data->m_itemType;
    }

    /// Number of items in the array.
    UInt32 size() const noexcept{
        return m_data->m_numItems;
    }

    /// Access contained value in array.
    DataType& at(std::size_t i) noexcept{
        return m_data->m_items[i];
    }

    /// Access contained value in array.
    const DataType& at(std::size_t i) const noexcept{
        return m_data->m_items[i];
    }

    /// Sets value in array.
    void set(std::size_t i, const DataType& val) noexcept{
        at(i) = val;
    }


    DataType& operator[](std::size_t i) noexcept{
        return at(i);
    }

    const DataType& operator[](std::size_t i) const noexcept{
        return at(i);
    }

    operator bool() const noexcept{
        return m_data;
    }


    iterator begin() noexcept{
        return m_data->m_items;
    }

    const_iterator begin() const noexcept{
        return cbegin();
    }

    const_iterator cbegin() const noexcept{
        return m_data->m_items;
    }

    iterator end() noexcept{
        return m_data->m_items + m_data->m_numItems;
    }

    const_iterator end() const noexcept{
        return cend();
    }

    const_iterator cend() const noexcept{
        return m_data->m_items + m_data->m_numItems;
    }

private:
    Array(Handle h) : m_data(h){}

    Detail::Lock<Detail::ArrayData<DataType> > m_data;

};

// disable Array for incompatible types
template<typename DataType>
class Array<Type::DontCare, DataType>;
template<typename DataType>
class Array<Type::Handle, DataType>;


/// Capability container holding an array of values,
/// and default and current indexes.
/// \tparam twty ID of the internal data type.
/// \tparam DataType Exported data type.
template<Type twty, typename DataType = typename Detail::Twty<twty>::Type>
class Enumeration {

    friend class Capability;

public:
    static constexpr const ConType contype = ConType::Enumeration;
    typedef DataType* iterator;
    typedef const DataType* const_iterator;

    /// Creates an invalid container.
    constexpr Enumeration() noexcept{}

    /// ID of the internal data type.
    Type type() const noexcept{
        return m_data->m_itemType;
    }

    /// Number of items in the array.
    UInt32 size() const noexcept{
        return m_data->m_numItems;
    }


    /// Index of the currently selected item.
    UInt32 currentIndex() const noexcept{
        return m_data->m_currIndex;
    }

    /// Sets index of the currently selected item.
    void setCurrentIndex(UInt32 index) noexcept{
        m_data->m_currIndex = index;
    }

    /// Item at the current index.
    DataType& currentItem() noexcept{
        return at(m_data->m_currIndex);
    }

    /// Item at the current index.
    const DataType& currentItem() const noexcept{
        return at(m_data->m_currIndex);
    }

    /// Sets item at the current index.
    void setCurrentItem(const DataType& item) noexcept{
        currentItem() = item;
    }


    /// Index of the default item.
    UInt32 defaultIndex() const noexcept{
        return m_data->m_defIndex;
    }

    /// Sets index of the default item.
    void setDefaultIndex(UInt32 index) noexcept{
        m_data->m_defIndex = index;
    }

    /// Item at the default index.
    DataType& defaultItem() noexcept{
        return at(m_data->m_defIndex);
    }

    /// Item at the default index.
    const DataType& defaultItem() const noexcept{
        return at(m_data->m_defIndex);
    }

    /// Sets item at the default index.
    void setDefaultItem(const DataType& item) noexcept{
        defaultItem() = item;
    }


    /// Access contained value in array.
    DataType& at(std::size_t i) noexcept{
        return m_data->m_items[i];
    }

    /// Access contained value in array.
    const DataType& at(std::size_t i) const noexcept{
        return m_data->m_items[i];
    }

    /// Sets value in array.
    void set(std::size_t i, const DataType& val) noexcept{
        at(i) = val;
    }


    DataType& operator[](std::size_t i) noexcept{
        return at(i);
    }

    const DataType& operator[](std::size_t i) const noexcept{
        return at(i);
    }

    operator bool() const noexcept{
        return m_data;
    }


    iterator begin() noexcept{
        return m_data->m_items;
    }

    const_iterator begin() const noexcept{
        return cbegin();
    }

    const_iterator cbegin() const noexcept{
        return m_data->m_items;
    }

    iterator end() noexcept{
        return m_data->m_items + m_data->m_numItems;
    }

    const_iterator end() const noexcept{
        return cend();
    }

    const_iterator cend() const noexcept{
        return m_data->m_items + m_data->m_numItems;
    }

private:
    Enumeration(Handle h) : m_data(h){}

    Detail::Lock<Detail::EnumerationData<DataType> > m_data;

};

// disable Enumeration for incompatible types
template<typename DataType>
class Enumeration<Type::DontCare, DataType>;
template<typename DataType>
class Enumeration<Type::Handle, DataType>;


/// Capability container holding a range of numeric values,
/// and default and current values.
/// \tparam twty ID of the internal data type.
/// \tparam DataType Exported data type.
template<Type twty, typename DataType = typename Detail::Twty<twty>::Type>
class Range {

    friend class Capability;
    static_assert(Detail::IsNumeric<DataType>::value, "not a numeric type");

private:
    static constexpr const ConType contype = ConType::Range;
    template<typename IterDataType>
    class IteratorImpl {

        friend class Range;

    public:
        constexpr IteratorImpl() noexcept :
            m_curr(), m_parent(nullptr){}

        IterDataType operator*() const noexcept{
            return m_curr;
        }

        IteratorImpl& operator++() noexcept{ // prefix
            m_curr += step();
            checkValue();
            return *this;
        }

        IteratorImpl operator++(int) noexcept{ // postfix
            IteratorImpl ret(*this);
            m_curr += step();
            checkValue();
            return ret;
        }

        IteratorImpl& operator--() noexcept{ // prefix
            m_curr -= step();
            return *this;
        }

        IteratorImpl operator--(int) noexcept{ // postfix
            IteratorImpl ret(*this);
            m_curr -= step();
            return ret;
        }

        bool operator==(const IteratorImpl& o) const noexcept{
            return m_curr == o.m_curr &&
                    (m_parent == o.m_parent ||
                        (m_parent && o.m_parent && step() == o.step())
                     );
        }

        bool operator!=(const IteratorImpl& o) const noexcept{
            return (*this == o);
        }

    private:
        IterDataType step() const noexcept{
            return m_parent->stepSize();
        }

        IterDataType max() const noexcept{
            return m_parent->maxValue();
        }

        void checkValue() noexcept{
            // avoid infinite loops in case no such N exists: `min + N * step == max`
            if (m_curr > max()){
                m_curr = max() + step();
            }
        }

        IteratorImpl(IterDataType curr, const Range& parent) noexcept :
            m_curr(curr), m_parent(&parent){}

        IterDataType m_curr;
        const Range* m_parent;

    };

public:
    typedef IteratorImpl<DataType> const_iterator;

    /// Creates an invalid container.
    constexpr Range() noexcept{}

    /// ID of the internal data type.
    Type type() const noexcept{
        return m_data->m_itemType;
    }

    /// Minimal value in the range.
    DataType minValue() const noexcept{
        return m_data->m_minValue;
    }

    /// Sets minimal value in the range.
    void setMinValue(DataType val) noexcept{
        m_data->m_minValue = val;
    }

    /// Maximal value in the range.
    DataType maxValue() const noexcept{
        return m_data->m_maxValue;
    }

    /// Sets maximal value in the range.
    void setMaxValue(DataType val) noexcept{
        m_data->m_maxValue = val;
    }

    /// Size of a single step.
    DataType stepSize() const noexcept{
        return m_data->m_stepSize;
    }

    ///Sets size of a single step.
    void setStepSize(DataType val) noexcept{
        m_data->m_stepSize = val;
    }

    /// Default value in the range.
    DataType defaultValue() const noexcept{
        return m_data->m_defValue;
    }

    /// Sets default value in the range.
    void setDefaultValue(DataType val) noexcept{
        m_data->m_defValue = val;
    }

    /// Current value in the range.
    DataType currentValue() const noexcept{
        return m_data->m_currValue;
    }

    /// Sets current value in the range.
    void setCurrentValue(DataType val) noexcept{
        m_data->m_currValue = val;
    }

    operator bool() const noexcept{
        return m_data;
    }

    const_iterator begin() const noexcept{
        return cbegin();
    }

    const_iterator cbegin() const noexcept{
        return const_iterator(m_data->m_minValue, *this);
    }

    const_iterator end() const noexcept{
        return cend();
    }

    const_iterator cend() const noexcept{
        auto step = m_data->m_stepSize;
        if (step != DataType()){
            return const_iterator(m_data->m_maxValue + step, *this);
        } else {
            return cbegin(); // no items with step equal to zero
        }
    }

private:
    Range(Handle h) : m_data(h){}

    Detail::Lock<Detail::RangeData<DataType> > m_data;

};

// disable Range for incompatible types
// (non-numeric types)
template<typename DataType>
class Range<Type::DontCare, DataType>;
template<typename DataType>
class Range<Type::Bool, DataType>;
template<typename DataType>
class Range<Type::Frame, DataType>;
template<typename DataType>
class Range<Type::Handle, DataType>;
template<typename DataType>
class Range<Type::Str32, DataType>;
template<typename DataType>
class Range<Type::Str64, DataType>;
template<typename DataType>
class Range<Type::Str128, DataType>;
template<typename DataType>
class Range<Type::Str255, DataType>;


namespace Detail {

template<Type type, bool, typename DataType>
class CapDataImpl;

template<Type type, typename DataType>
class CapData;

/// Capability iterator.
/// The default implementation is designed for non-numeric values.
/// Meaning it can't handle ranges.
template<Type type, typename DataType, bool numeric> // false
class CapIterator {

    friend class Capability;

    template<Type, bool, typename>
    friend class CapDataImpl;

public:
    constexpr CapIterator() noexcept :
        m_ptr(nullptr){}

    DataType& operator*() const noexcept{
        return *m_ptr;
    }

    CapIterator& operator++() noexcept{ // prefix
        ++m_ptr;
        return *this;
    }

    CapIterator operator++(int) noexcept{ // postfix
        CapIterator ret(*this);
        ++m_ptr;
        return ret;
    }

    CapIterator& operator--() noexcept{ // prefix
        --m_ptr;
        return *this;
    }

    CapIterator operator--(int) noexcept{ // postfix
        CapIterator ret(*this);
        --m_ptr;
        return ret;
    }

    bool operator==(const CapIterator& o) const noexcept{
        return m_ptr == o.m_ptr;
    }

    bool operator!=(const CapIterator& o) const noexcept{
        return !(*this == o);
    }

private:
    constexpr CapIterator(DataType* ptr) noexcept :
        m_ptr(ptr){}

    DataType* m_ptr;

};

/// Capability iterator.
/// This specialization can handles numeric values only.
/// Ranges included.
template<Type type, typename DataType>
class CapIterator<type, DataType, true> {

    friend class Capability;

    template<Type, bool, typename>
    friend class CapDataImpl;

public:
    typedef typename std::remove_const<DataType>::type ReturnType;

    constexpr CapIterator() noexcept :
        m_ptr(nullptr), m_isPtr(true){}

    ReturnType operator*() const noexcept{
        if (m_isPtr){
            return *m_ptr;
        } else {
            return *m_rng;
        }
    }

    CapIterator& operator++() noexcept{ // prefix
        if (m_isPtr){
            ++m_ptr;
        } else {
            ++m_rng;
        }

        return *this;
    }

    CapIterator operator++(int) noexcept{ // postfix
        CapIterator ret(*this);
        if (m_isPtr){
            ++m_ptr;
        } else {
            ++m_rng;
        }

        return ret;
    }

    CapIterator& operator--() noexcept{ // prefix
        if (m_isPtr){
            --m_ptr;
        } else {
            --m_rng;
        }

        return *this;
    }

    CapIterator operator--(int) noexcept{ // postfix
        CapIterator ret(*this);
        if (m_isPtr){
            --m_ptr;
        } else {
            --m_rng;
        }

        return ret;
    }

    bool operator==(const CapIterator& o) const noexcept{
        if (m_isPtr != o.m_isPtr){
            return false;
        }

        return m_isPtr ? m_ptr == o.m_ptr : m_rng == o.m_rng;
    }

    bool operator!=(const CapIterator& o) const noexcept{
        return !(*this == o);
    }

private:
    constexpr CapIterator(DataType* ptr) noexcept :
        m_ptr(ptr), m_isPtr(true){}

    constexpr CapIterator(typename Range<type, ReturnType>::const_iterator rng) noexcept :
        m_rng(rng), m_isPtr(false){}

    union {
        DataType* m_ptr;
        typename Range<type, ReturnType>::const_iterator m_rng;
    };
    bool m_isPtr;

};

/// Capability iterator lock implementation.
/// The default implementation is designed for non-numeric values.
/// Meaning it can't handle ranges.
template<Type type, bool numeric, typename DataType = typename Detail::Twty<type>::Type> // numeric=false
class CapDataImpl {

    friend class Capability;

    template<Type, typename>
    friend class CapData;

public:
    typedef CapIterator<type, const DataType, numeric> const_iterator;

    /// Creates an invalid container.
    constexpr CapDataImpl() noexcept :
        m_data(){

        static_assert(type != Type::DontCare, "type may not be DontCare");
        static_assert(sizeof(typename Detail::Twty<type>::Type) == sizeof(DataType), "type sizes dont match");
    }

    const_iterator begin() const noexcept{
        return cbegin();
    }

    const_iterator cbegin() const noexcept{
        return const_iterator(reinterpret_cast<DataType*>(m_data.data() + offset()));
    }

    const_iterator end() const noexcept{
        return cend();
    }

    const_iterator cend() const noexcept{
        return const_iterator(reinterpret_cast<DataType*>(m_data.data() + offset()) + size());
    }

    UInt32 size() const noexcept{
        switch (m_conType){
            case ConType::Array:
            case ConType::Enumeration:
                return reinterpret_cast<Detail::ArrayData<DataType>*>(m_data.data())->m_numItems;
            case ConType::OneValue:
                return 1;
            case ConType::Range:
            default:
                return 0; // should not happen
        }
    }

private:
    CapDataImpl(const Capability& cap);

    UInt32 offset() const noexcept{
        switch (m_conType){
            case ConType::Array:
                return sizeof(Type) + sizeof(UInt32);
            case ConType::Enumeration:
                return sizeof(Type) + 3 * sizeof(UInt32);
            case ConType::OneValue:
                return sizeof(Type);
            case ConType::Range:
            default:
                return 0; // should not happen
        }
    }

    ConType m_conType;
    Detail::Lock<char> m_data; // actual type resolved at runtime

};

/// Capability iterator lock implementation.
/// This specialization can handles numeric values only.
/// Ranges included.
template<Type type, typename DataType>
class CapDataImpl<type, true, DataType> {

    friend class Capability;

    template<Type, typename>
    friend class CapData;

public:
    typedef CapIterator<type, const DataType, true> const_iterator;

    /// Creates an invalid container.
    constexpr CapDataImpl() noexcept :
        m_data(){

        static_assert(type != Type::DontCare, "type may not be DontCare");
        static_assert(sizeof(typename Detail::Twty<type>::Type) == sizeof(DataType), "type sizes dont match");
    }

    const_iterator begin() const noexcept{
        return cbegin();
    }

    const_iterator cbegin() const noexcept{
        if (m_conType != ConType::Range){
            return const_iterator(reinterpret_cast<DataType*>(m_data.data() + offset()));
        } else {
            const auto& rng = *Detail::alias_cast<const Range<type, DataType>*>(&m_data);
            return const_iterator(rng.cbegin());
        }
    }

    const_iterator end() const noexcept{
        return cend();
    }

    const_iterator cend() const noexcept{
        if (m_conType != ConType::Range){
            return const_iterator(reinterpret_cast<DataType*>(m_data.data() + offset()) + size());
        } else {
            const auto& rng = *Detail::alias_cast<const Range<type, DataType>*>(&m_data);
            return const_iterator(rng.cend());
        }
    }

    UInt32 size() const noexcept{
        switch (m_conType){
            case ConType::Array:
            case ConType::Enumeration:
                return reinterpret_cast<Detail::ArrayData<DataType>*>(m_data.data())->m_numItems;
            case ConType::OneValue:
                return 1;
            case ConType::Range: {
                auto& rng = *reinterpret_cast<Detail::RangeData<DataType>*>(m_data.data());
                if (rng.m_stepSize != DataType()){
                    return static_cast<UInt32>((Detail::abs(rng.m_maxValue - rng.m_minValue) / rng.m_stepSize).toFloat()) + 1;
                } else {
                    return 0;
                }
            }
            default:
                return 0; // should not happen
        }
    }

private:
    CapDataImpl(const Capability& cap);

    UInt32 offset() const noexcept{
        switch (m_conType){
            case ConType::Array:
                return sizeof(Type) + sizeof(UInt32);
            case ConType::Enumeration:
                return sizeof(Type) + 3 * sizeof(UInt32);
            case ConType::OneValue:
                return sizeof(Type);
            case ConType::Range:
            default:
                return 0; // should not happen
        }
    }

    ConType m_conType;
    Detail::Lock<char> m_data; // actual type resolved at runtime

};

/// Capability iterator lock.
template<Type type, typename DataType>
class CapData : public CapDataImpl<type, IsNumeric<DataType>::value, DataType> {

    typedef CapDataImpl<type, IsNumeric<DataType>::value, DataType> Base;

public:
    constexpr CapData() noexcept{}

    CapData(const Capability& cap) :
        Base(cap){}

};


/// Capability current item implementation.
/// The default implementation is designed for non-numeric values.
/// Meaning it can't handle ranges.
template<Type type, typename DataType, bool isNumeric> // false
struct CurrentItemImpl {
    static DataType item(Capability& cap);
};

/// Capability current item implementation.
/// This specialization can handles numeric values only.
/// Ranges included.
template<Type type, typename DataType>
struct CurrentItemImpl<type, DataType, true> {
    static DataType item(Capability& cap);
};

/// Capability current item.
template<Type type, typename DataType>
struct CurrentItem : CurrentItemImpl<type, DataType, IsNumeric<DataType>::value> {

};

}

/// Base capability exception.
class CapabilityException : public Exception {

public:
    virtual const char* what() const noexcept override{
        return "Capability handling error.";
    }

};

/// Invalid or unsupported container capability exception.
class ContainerException : public CapabilityException {

public:
    virtual const char* what() const noexcept override{
        return "Unexpected container.";
    }

};

/// Invalid, unsupported or mismatched item type identifier capability exception.
class ItemTypeException : public CapabilityException {

public:
    virtual const char* what() const noexcept override{
        return "Invalid item type.";
    }

};

/// No data capability exception.
/// Capability does not contain any data (container).
class DataException : public CapabilityException {

public:
    virtual const char* what() const noexcept override{
        return "No data.";
    }

};

TWPP_DETAIL_PACK_BEGIN
/// TWAIN capability.
/// Any access to containers must be finished before destroying
/// the according capability instance.
class Capability {

    template<Type, bool, typename>
    friend class Detail::CapDataImpl;

public:
    /// Creates capability holding OneValue container.
    /// \tparam type ID of the internal data type.
    /// \tparam DataType Exported data type.
    /// \param cap Capability type.
    /// \param value Initial value.
    /// \throw std::bad_alloc
    template<Type type, typename DataType>
    static Capability createOneValue(CapType cap, const DataType& value = DataType()){
        Capability ret(cap, ConType::OneValue, type, sizeof(Detail::OneValueData<DataType>));
        auto ov = ret.oneValue<type, DataType>();
        ov.setItem(value);
        return std::move(ret);
    }

    /// Creates capability holding OneValue container.
    /// \tparam type ID of the internal data type.
    /// \param cap Capability type.
    /// \param value Initial value.
    /// \throw std::bad_alloc
    template<Type type>
    static Capability createOneValue(CapType cap, const typename Detail::Twty<type>::Type& value = typename Detail::Twty<type>::Type()){
        return createOneValue<type, typename Detail::Twty<type>::Type>(cap, value);
    }

    /// Creates capability holding OneValue container.
    /// \tparam T Data type.
    /// \param cap Capability type.
    /// \param value Initial value.
    /// \throw std::bad_alloc
    template<typename T>
    static Capability createOneValue(CapType cap, const T& value = T()){
        return createOneValue<Detail::Tytw<T>::twty, T>(cap, value);
    }

    /// Creates capability holding OneValue container.
    /// \tparam cap Capability type. Data types are set accordingly.
    /// \param value Initial value.
    /// \throw std::bad_alloc
    template<CapType cap>
    static Capability createOneValue(const typename Detail::Cap<cap>::DataType& value = typename Detail::Cap<cap>::DataType()){
        return createOneValue<Detail::Cap<cap>::twty, typename Detail::Cap<cap>::DataType>(cap, value);
    }


    /// Creates capability holding Array container.
    /// \tparam type ID of the internal data type.
    /// \tparam DataType Exported data type.
    /// \param cap Capability type.
    /// \param size Number of elements in the array.
    /// \throw std::bad_alloc
    template<Type type, typename DataType>
    static Capability createArray(CapType cap, UInt32 size){
        Capability ret(cap, ConType::Array, type, sizeof(Detail::ArrayData<DataType>) - sizeof(DataType) + size * sizeof(DataType));
        auto arr = ret.array<type, DataType>();
        arr.m_data->m_numItems = size;
        return std::move(ret);
    }

    /// Creates capability holding Array container.
    /// \tparam type ID of the internal data type.
    /// \param cap Capability type.
    /// \param size Number of elements in the array.
    /// \throw std::bad_alloc
    template<Type type>
    static Capability createArray(CapType cap, UInt32 size){
        return createArray<type, typename Detail::Twty<type>::Type>(cap, size);
    }

    /// Creates capability holding Array container.
    /// \tparam type ID of the internal data type.
    /// \tparam DataType Exported data type.
    /// \param cap Capability type.
    /// \param values Initial values in the array.
    /// \throw std::bad_alloc
    template<Type type, typename DataType>
    static Capability createArray(CapType cap, std::initializer_list<DataType> values){
        Capability ret = createArray<type, DataType>(cap, values.size());
        auto arr = ret.array<type, DataType>();

        UInt32 i = 0;
        for (const auto& val : values){
            arr[i] = val;
            i++;
        }

        return std::move(ret);
    }

    /// Creates capability holding Array container.
    /// \tparam type ID of the internal data type.
    /// \param cap Capability type.
    /// \param values Initial values in the array.
    /// \throw std::bad_alloc
    template<Type type>
    static Capability createArray(CapType cap, std::initializer_list<typename Detail::Twty<type>::Type> values){
        return createArray<type, typename Detail::Twty<type>::Type>(cap, values);
    }

    /// Creates capability holding Array container.
    /// \tparam T Data type.
    /// \param cap Capability type.
    /// \param size Number of elements in the array.
    /// \throw std::bad_alloc
    template<typename T>
    static Capability createArray(CapType cap, UInt32 size){
        return createArray<Detail::Tytw<T>::twty, T>(cap, size);
    }

    /// Creates capability holding Array container.
    /// \tparam T Data type.
    /// \param cap Capability type.
    /// \param values Initial values in the array.
    /// \throw std::bad_alloc
    template<typename T>
    static Capability createArray(CapType cap, std::initializer_list<T> values){
        return createArray<Detail::Tytw<T>::twty, T>(cap, values);
    }

    /// Creates capability holding Array container.
    /// \tparam cap Capability type. Data types are set accordingly.
    /// \param size Number of elements in the array.
    /// \throw std::bad_alloc
    template<CapType cap>
    static Capability createArray(UInt32 size){
        return createArray<Detail::Cap<cap>::twty, typename Detail::Cap<cap>::DataType>(cap, size);
    }

    /// Creates capability holding Array container.
    /// \tparam cap Capability type. Data types are set accordingly.
    /// \param values Initial values in the array.
    /// \throw std::bad_alloc
    template<CapType cap>
    static Capability createArray(std::initializer_list<typename Detail::Cap<cap>::DataType> values){
        return createArray<Detail::Cap<cap>::twty, typename Detail::Cap<cap>::DataType>(cap, values);
    }


    /// Creates capability holding Enumeration container.
    /// \tparam type ID of the internal data type.
    /// \tparam DataType Exported data type.
    /// \param cap Capability type.
    /// \param size Number of elements in the array.
    /// \param currIndex Index of the currently selected item.
    /// \param defIndex Index of the default item.
    /// \throw std::bad_alloc
    template<Type type, typename DataType>
    static Capability createEnumeration(CapType cap, UInt32 size, UInt32 currIndex = 0, UInt32 defIndex = 0){
        Capability ret(cap, ConType::Enumeration, type, sizeof(Detail::EnumerationData<DataType>) - sizeof(DataType) + size * sizeof(DataType));
        auto enm = ret.enumeration<type, DataType>();
        enm.m_data->m_numItems = size;
        enm.m_data->m_currIndex = currIndex;
        enm.m_data->m_defIndex = defIndex;
        return std::move(ret);
    }

    /// Creates capability holding Enumeration container.
    /// \tparam type ID of the internal data type.
    /// \param cap Capability type.
    /// \param size Number of elements in the array.
    /// \param currIndex Index of the currently selected item.
    /// \param defIndex Index of the default item.
    /// \throw std::bad_alloc
    template<Type type>
    static Capability createEnumeration(CapType cap, UInt32 size, UInt32 currIndex = 0, UInt32 defIndex = 0){
        return createEnumeration<type, typename Detail::Twty<type>::Type>(cap, size, currIndex, defIndex);
    }

    /// Creates capability holding Enumeration container.
    /// \tparam type ID of the internal data type.
    /// \tparam DataType Exported data type.
    /// \param cap Capability type.
    /// \param values Initial values in the array.
    /// \param currIndex Index of the currently selected item.
    /// \param defIndex Index of the default item.
    /// \throw std::bad_alloc
    template<Type type, typename DataType>
    static Capability createEnumeration(CapType cap, std::initializer_list<DataType> values, UInt32 currIndex = 0, UInt32 defIndex = 0){
        Capability ret = createEnumeration<type, DataType>(cap, values.size(), currIndex, defIndex);
        auto enm = ret.enumeration<type, DataType>();

        UInt32 i = 0;
        for (const auto& val : values){
            enm[i] = val;
            i++;
        }

        return std::move(ret);
    }

    /// Creates capability holding Enumeration container.
    /// \tparam type ID of the internal data type.
    /// \param cap Capability type.
    /// \param values Initial values in the array.
    /// \param currIndex Index of the currently selected item.
    /// \param defIndex Index of the default item.
    /// \throw std::bad_alloc
    template<Type type>
    static Capability createEnumeration(CapType cap, std::initializer_list<typename Detail::Twty<type>::Type> values, UInt32 currIndex = 0, UInt32 defIndex = 0){
        return createEnumeration<type, typename Detail::Twty<type>::Type>(cap, values, currIndex, defIndex);
    }

    /// Creates capability holding Enumeration container.
    /// \tparam T Data type.
    /// \param cap Capability type.
    /// \param size Number of elements in the array.
    /// \param currIndex Index of the currently selected item.
    /// \param defIndex Index of the default item.
    /// \throw std::bad_alloc
    template<typename T>
    static Capability createEnumeration(CapType cap, UInt32 size, UInt32 currIndex = 0, UInt32 defIndex = 0){
        return createEnumeration<Detail::Tytw<T>::twty, T>(cap, size, currIndex, defIndex);
    }

    /// Creates capability holding Enumeration container.
    /// \tparam T Data type.
    /// \param cap Capability type.
    /// \param values Initial values in the array.
    /// \param currIndex Index of the currently selected item.
    /// \param defIndex Index of the default item.
    /// \throw std::bad_alloc
    template<typename T>
    static Capability createEnumeration(CapType cap, std::initializer_list<T> values, UInt32 currIndex = 0, UInt32 defIndex = 0){
        return createEnumeration<Detail::Tytw<T>::twty, T>(cap, values, currIndex, defIndex);
    }

    /// Creates capability holding Enumeration container.
    /// \tparam cap Capability type. Data types are set accordingly.
    /// \param size Number of elements in the array.
    /// \param currIndex Index of the currently selected item.
    /// \param defIndex Index of the default item.
    /// \throw std::bad_alloc
    template<CapType cap>
    static Capability createEnumeration(UInt32 size, UInt32 currIndex = 0, UInt32 defIndex = 0){
        return createEnumeration<Detail::Cap<cap>::twty, typename Detail::Cap<cap>::DataType>(cap, size, currIndex, defIndex);
    }

    /// Creates capability holding Enumeration container.
    /// \tparam cap Capability type. Data types are set accordingly.
    /// \param values Initial values in the array.
    /// \param currIndex Index of the currently selected item.
    /// \param defIndex Index of the default item.
    /// \throw std::bad_alloc
    template<CapType cap>
    static Capability createEnumeration(std::initializer_list<typename Detail::Cap<cap>::DataType> values, UInt32 currIndex = 0, UInt32 defIndex = 0){
        return createEnumeration<Detail::Cap<cap>::twty, typename Detail::Cap<cap>::DataType>(cap, values, currIndex, defIndex);
    }


    /// Creates capability holding Range container.
    /// \tparam type ID of the internal data type.
    /// \tparam DataType Exported data type.
    /// \param cap Capability type.
    /// \param min Minimal range value.
    /// \param max Maximal range value.
    /// \param step Size of a single step.
    /// \param curr Current value.
    /// \param def Default value.
    /// \throw std::bad_alloc
    template<Type type, typename DataType>
    static Capability createRange(CapType cap, DataType min, DataType max, DataType step, DataType curr, DataType def){
        Capability ret(cap, ConType::Range, type, sizeof(Detail::OneValueData<DataType>));
        auto rng = ret.range<type, DataType>();
        rng.setMinValue(min);
        rng.setMaxValue(max);
        rng.setStepSize(step);
        rng.setCurrentValue(curr);
        rng.setDefaultValue(def);
        return std::move(ret);
    }

    /// Creates capability holding Range container.
    /// \tparam type ID of the internal data type.
    /// \param cap Capability type.
    /// \param min Minimal range value.
    /// \param max Maximal range value.
    /// \param step Size of a single step.
    /// \param curr Current value.
    /// \param def Default value.
    /// \throw std::bad_alloc
    template<Type type>
    static Capability createRange(
            CapType cap,
            typename Detail::Twty<type>::Type min,
            typename Detail::Twty<type>::Type max,
            typename Detail::Twty<type>::Type step,
            typename Detail::Twty<type>::Type curr,
            typename Detail::Twty<type>::Type def
    ){
        return createRange<type, typename Detail::Twty<type>::Type>(cap, min, max, step, curr, def);
    }

    /// Creates capability holding Range container.
    /// \tparam T Data type.
    /// \param cap Capability type.
    /// \param min Minimal range value.
    /// \param max Maximal range value.
    /// \param step Size of a single step.
    /// \param curr Current value.
    /// \param def Default value.
    /// \throw std::bad_alloc
    template<typename T>
    static Capability createRange(CapType cap, T min, T max, T step, T curr, T def){
        return createRange<Detail::Tytw<T>::twty, T>(cap, min, max, step, curr, def);
    }

    /// Creates capability holding Range container.
    /// \tparam cap Capability type. Data types are set accordingly.
    /// \param min Minimal range value.
    /// \param max Maximal range value.
    /// \param step Size of a single step.
    /// \param curr Current value.
    /// \param def Default value.
    /// \throw std::bad_alloc
    template<CapType cap>
    static Capability createRange(
            typename Detail::Cap<cap>::DataType min,
            typename Detail::Cap<cap>::DataType max,
            typename Detail::Cap<cap>::DataType step,
            typename Detail::Cap<cap>::DataType curr,
            typename Detail::Cap<cap>::DataType def
    ){
        return createRange<Detail::Cap<cap>::twty, typename Detail::Cap<cap>::DataType>(
                    cap, min, max, step, curr, def);
    }


    /// Creates capability of the supplied type without any data.
    /// Useful for retrieving data from data source.
    explicit Capability(CapType cap) noexcept :
        m_cap(cap), m_conType(ConType::DontCare), m_cont(){}

    Capability(Capability&&) = default;
    Capability& operator=(Capability&&) = default;

    /// Capability type.
    CapType type() const noexcept{
        return m_cap;
    }

    /// Container type.
    ConType container() const noexcept{
        return m_conType;
    }

    /// Item type.
    /// Valid only if the capability contains data.
    /// \throw DataException When there is no data.
    Type itemType() const{
        if (!m_cont){
            throw DataException();
        }

        return *m_cont.lock<Type>().data();
    }

    operator bool() const noexcept{
        return m_cont;
    }

    /// Contained OneValue container.
    /// \tparam type ID of the internal data type.
    /// \tparam DataType Exported data type.
    /// \throw DataException When there is no data.
    /// \throw ContainerException When container is not OneValue.
    /// \throw ItemTypeException When item type does not match.
    template<Type type, typename DataType>
    OneValue<type, DataType> oneValue(){
        return containerCheck<OneValue, type, DataType>();
    }

    /// Contained OneValue container.
    /// \tparam type ID of the internal data type.
    /// \throw DataException When there is no data.
    /// \throw ContainerException When container is not OneValue.
    /// \throw ItemTypeException When item type does not match.
    template<Type type>
    OneValue<type, typename Detail::Twty<type>::Type> oneValue(){
        return oneValue<type, typename Detail::Twty<type>::Type>();
    }

    /// Contained OneValue container.
    /// \tparam T Data type.
    /// \throw DataException When there is no data.
    /// \throw ContainerException When container is not OneValue.
    /// \throw ItemTypeException When item type does not match.
    template<typename T>
    OneValue<Detail::Tytw<T>::twty, T> oneValue(){
        return oneValue<Detail::Tytw<T>::twty, T>();
    }

    /// Contained OneValue container.
    /// \tparam cap Capability type. Data types are set accordingly.
    /// \throw DataException When there is no data.
    /// \throw ContainerException When container is not OneValue.
    /// \throw ItemTypeException When item type does not match.
    template<CapType cap>
    OneValue<Detail::Cap<cap>::twty, typename Detail::Cap<cap>::DataType> oneValue(){
        return oneValue<Detail::Cap<cap>::twty, typename Detail::Cap<cap>::DataType>();
    }

    /// Contained Array container.
    /// \tparam type ID of the internal data type.
    /// \tparam DataType Exported data type.
    /// \throw DataException When there is no data.
    /// \throw ContainerException When container is not Array.
    /// \throw ItemTypeException When item type does not match.
    template<Type type, typename DataType>
    Array<type, DataType> array(){
        return containerCheck<Array, type, DataType>();
    }

    /// Contained Array container.
    /// \tparam type ID of the internal data type.
    /// \throw DataException When there is no data.
    /// \throw ContainerException When container is not Array.
    /// \throw ItemTypeException When item type does not match.
    template<Type type>
    Array<type, typename Detail::Twty<type>::Type> array(){
        return array<type, typename Detail::Twty<type>::Type>();
    }

    /// Contained Array container.
    /// \tparam T Data type.
    /// \throw DataException When there is no data.
    /// \throw ContainerException When container is not Array.
    /// \throw ItemTypeException When item type does not match.
    template<typename T>
    Array<Detail::Tytw<T>::twty, T> array(){
        return array<Detail::Tytw<T>::twty, T>();
    }

    /// Contained Array container.
    /// \tparam cap Capability type. Data types are set accordingly.
    /// \throw DataException When there is no data.
    /// \throw ContainerException When container is not Array.
    /// \throw ItemTypeException When item type does not match.
    template<CapType cap>
    Array<Detail::Cap<cap>::twty, typename Detail::Cap<cap>::DataType> array(){
        return array<Detail::Cap<cap>::twty, typename Detail::Cap<cap>::DataType>();
    }

    /// Contained Enumeration container.
    /// \tparam type ID of the internal data type.
    /// \tparam DataType Exported data type.
    /// \throw DataException When there is no data.
    /// \throw ContainerException When container is not Enumeration.
    /// \throw ItemTypeException When item type does not match.
    template<Type type, typename DataType>
    Enumeration<type, DataType> enumeration(){
        return containerCheck<Enumeration, type, DataType>();
    }

    /// Contained Enumeration container.
    /// \tparam type ID of the internal data type.
    /// \throw DataException When there is no data.
    /// \throw ContainerException When container is not Enumeration.
    /// \throw ItemTypeException When item type does not match.
    template<Type type>
    Enumeration<type, typename Detail::Twty<type>::Type> enumeration(){
        return enumeration<type, typename Detail::Twty<type>::Type>();
    }

    /// Contained Enumeration container.
    /// \tparam T Data type.
    /// \throw DataException When there is no data.
    /// \throw ContainerException When container is not Enumeration.
    /// \throw ItemTypeException When item type does not match.
    template<typename T>
    Enumeration<Detail::Tytw<T>::twty, T> enumeration(){
        return enumeration<Detail::Tytw<T>::twty, T>();
    }

    /// Contained Enumeration container.
    /// \tparam cap Capability type. Data types are set accordingly.
    /// \throw DataException When there is no data.
    /// \throw ContainerException When container is not Enumeration.
    /// \throw ItemTypeException When item type does not match.
    template<CapType cap>
    Enumeration<Detail::Cap<cap>::twty, typename Detail::Cap<cap>::DataType> enumeration(){
        return enumeration<Detail::Cap<cap>::twty, typename Detail::Cap<cap>::DataType>();
    }

    /// Contained Range container.
    /// \tparam type ID of the internal data type.
    /// \tparam DataType Exported data type.
    /// \throw DataException When there is no data.
    /// \throw ContainerException When container is not Enumeration.
    /// \throw ItemTypeException When item type does not match.
    template<Type type, typename DataType>
    Range<type, DataType> range(){
        return containerCheck<Range, type, DataType>();
    }

    /// Contained Range container.
    /// \tparam type ID of the internal data type.
    /// \throw DataException When there is no data.
    /// \throw ContainerException When container is not Enumeration.
    /// \throw ItemTypeException When item type does not match.
    template<Type type>
    Range<type, typename Detail::Twty<type>::Type> range(){
        return range<type, typename Detail::Twty<type>::Type>();
    }

    /// Contained Range container.
    /// \tparam T Data type.
    /// \throw DataException When there is no data.
    /// \throw ContainerException When container is not Range.
    /// \throw ItemTypeException When item type does not match.
    template<typename T>
    Range<Detail::Tytw<T>::twty, T> range(){
        return range<Detail::Tytw<T>::twty, T>();
    }

    /// Contained Range container.
    /// \tparam cap Capability type. Data types are set accordingly.
    /// \throw DataException When there is no data.
    /// \throw ContainerException When container is not Range.
    /// \throw ItemTypeException When item type does not match.
    template<CapType cap>
    Range<Detail::Cap<cap>::twty, typename Detail::Cap<cap>::DataType> range(){
        return range<Detail::Cap<cap>::twty, typename Detail::Cap<cap>::DataType>();
    }

    template<Type type, typename DataType>
    using Data = Detail::CapData<type, DataType>;

    /// Returns a data container for iterating over all possible values.
    /// Use this only if you don't care about current or default values and container type.
    /// \tparam type ID of the internal data type.
    /// \tparam DataType Exported data type.
    /// \throw DataException When there is no data.
    /// \throw ContainerException When container is invalid.
    /// \throw ItemTypeException When item type does not match.
    template<Type type, typename DataType>
    Data<type, DataType> data() const{
        return *this;
    }

    /// Returns a data container for iterating over all possible values.
    /// Use this only if you don't care about current or default values and container type.
    /// \tparam type ID of the internal data type.
    /// \throw DataException When there is no data.
    /// \throw ContainerException When container is invalid.
    /// \throw ItemTypeException When item type does not match.
    template<Type type>
    Data<type, typename Detail::Twty<type>::Type> data() const{
        return *this;
    }

    /// Returns a data container for iterating over all possible values.
    /// Use this only if you don't care about current or default values and container type.
    /// \tparam T Data type.
    /// \throw DataException When there is no data.
    /// \throw ContainerException When container is invalid.
    /// \throw ItemTypeException When item type does not match.
    template<typename T>
    Data<Detail::Tytw<T>::twty, T> data() const{
        return *this;
    }

    /// Returns a data container for iterating over all possible values.
    /// Use this only if you don't care about current or default values and container type.
    /// \tparam cap Capability type. Data types are set accordingly.
    /// \throw DataException When there is no data.
    /// \throw ContainerException When container is invalid.
    /// \throw ItemTypeException When item type does not match.
    template<CapType cap>
    Data<Detail::Cap<cap>::twty, typename Detail::Cap<cap>::DataType> data() const{
        return *this;
    }


    /// Returns a copy of the current item of this capability.
    /// Can be used only with Enumeration, OneValue, and Range containers.
    /// \tparam type ID of the internal data type.
    /// \tparam DataType Exported data type.
    /// \throw DataException When there is no data.
    /// \throw ContainerException When container is not Enumeration, OneValue, nor Range.
    /// \throw ItemTypeException When item type does not match.
    template<Type type, typename DataType>
    DataType currentItem(){
        return Detail::CurrentItem<type, DataType>::item(*this);
    }

    /// Returns a copy of the current item of this capability.
    /// Can be used only with Enumeration, OneValue, and Range containers.
    /// \tparam type ID of the internal data type.
    /// \throw DataException When there is no data.
    /// \throw ContainerException When container is not Enumeration, OneValue, nor Range.
    /// \throw ItemTypeException When item type does not match.
    template<Type type>
    typename Detail::Twty<type>::Type currentItem(){
        return currentItem<type, typename Detail::Twty<type>::Type>();
    }

    /// Returns a copy of the current item of this capability.
    /// Can be used only with Enumeration, OneValue, and Range containers.
    /// \tparam T Data type.
    /// \throw DataException When there is no data.
    /// \throw ContainerException When container is not Enumeration, OneValue, nor Range.
    /// \throw ItemTypeException When item type does not match.
    template<typename T>
    T currentItem(){
        return currentItem<Detail::Tytw<T>::twty, T>();
    }

    /// Returns a copy of the current item of this capability.
    /// Can be used only with Enumeration, OneValue, and Range containers.
    /// \tparam cap Capability type. Data types are set accordingly.
    /// \throw DataException When there is no data.
    /// \throw ContainerException When container is not Enumeration, OneValue, nor Range.
    /// \throw ItemTypeException When item type does not match.
    template<CapType cap>
    typename Detail::Cap<cap>::DataType currentItem(){
        return currentItem<Detail::Cap<cap>::twty, typename Detail::Cap<cap>::DataType>();
    }

private:
    /// \throw DataException
    /// \throw ContainerException
    /// \throw ItemTypeException
    Capability(CapType cap, ConType conType, Type twty, UInt32 size) :
        m_cap(cap), m_conType(conType), m_cont(Detail::alloc(size)){

        *m_cont.lock<Type>().data() = twty;
    }

    template<template<Type, typename> class Container, Type type, typename DataType>
    Container<type, DataType> containerCheck(){
        static_assert(type != Type::DontCare, "type may not be DontCare");
        static_assert(sizeof(typename Detail::Twty<type>::Type) == sizeof(DataType), "type sizes dont match");

        if (!m_cont){
            throw DataException();
        }

        if (Container<type, DataType>::contype != container()){
            throw ContainerException();
        }

        Container<type, DataType> ret(m_cont.get());
        if (type != ret.type()){
            throw ItemTypeException();
        }

        return std::move(ret);
    }

    CapType m_cap;
    ConType m_conType;
    Detail::UniqueHandle m_cont;

};
TWPP_DETAIL_PACK_END

/// Invalid, unsupported or mismatched item type identifier capability exception.
/// Holds the Capability instance that caused the exception.
class CapItemTypeException : public ItemTypeException {

public:
    CapItemTypeException(Capability cap) noexcept :
        m_cap(std::move(cap)){}

    CapItemTypeException(CapItemTypeException&&) = default;
    CapItemTypeException& operator=(CapItemTypeException&&) = default;

    CapItemTypeException(const CapItemTypeException&) = delete;
    CapItemTypeException& operator=(const CapItemTypeException&) = delete;

    Capability& capability() noexcept{
        return m_cap;
    }

    const Capability& capability() const noexcept{
        return m_cap;
    }

    virtual const char* what() const noexcept override{
        return "Unexpected item type.";
    }

private:
    Capability m_cap;

};

/// Invalid, unexpected, unmatched capability type.
/// Holds the Capability instance that caused the exception.
class CapTypeException : public CapabilityException {

public:
    CapTypeException(Capability cap) noexcept :
        m_cap(std::move(cap)){}

    CapTypeException(CapTypeException&&) = default;
    CapTypeException& operator=(CapTypeException&&) = default;

    CapTypeException(const CapTypeException&) = delete;
    CapTypeException& operator=(const CapTypeException&) = delete;

    Capability& capability() noexcept{
        return m_cap;
    }

    const Capability& capability() const noexcept{
        return m_cap;
    }

    virtual const char* what() const noexcept override{
        return "Unexpected capability type.";
    }

private:
    Capability m_cap;

};

class Source;

/// Convenience Capability wrapper class.
/// Guaranteed to contain the same capability type and item type
/// throughout the whole lifetime.
template<CapType cap>
class Cap {

    friend class Source;

public:
    typedef typename Detail::Cap<cap>::DataType DataType;
    static constexpr const Type twty = Detail::Cap<cap>::twty;

    /// Creates capability holding OneValue container.
    /// \param value Initial value.
    /// \throw std::bad_alloc
    static Cap createOneValue(const DataType& value = DataType()){
        return Cap(Capability::createOneValue<cap>(value), 0);
    }


    /// Creates capability holding Array container.
    /// \param size Number of elements in the array.
    /// \throw std::bad_alloc
    static Cap createArray(UInt32 size){
        return Cap(Capability::createArray<cap>(size), 0);
    }

    /// Creates capability holding Array container.
    /// \param values Initial values in the array.
    /// \throw std::bad_alloc
    static Cap createArray(std::initializer_list<DataType> values){
        return Cap(Capability::createArray<cap>(values), 0);
    }


    /// Creates capability holding Enumeration container.
    /// \param size Number of elements in the array.
    /// \param currIndex Index of the currently selected item.
    /// \param defIndex Index of the default item.
    /// \throw std::bad_alloc
    static Cap createEnumeration(UInt32 size, UInt32 currIndex = 0, UInt32 defIndex = 0){
        return Cap(Capability::createEnumeration<cap>(size, currIndex, defIndex), 0);
    }

    /// Creates capability holding Enumeration container.
    /// \param values Initial values in the array.
    /// \param currIndex Index of the currently selected item.
    /// \param defIndex Index of the default item.
    /// \throw std::bad_alloc
    static Cap createEnumeration(std::initializer_list<DataType> values, UInt32 currIndex = 0, UInt32 defIndex = 0){
        return Cap(Capability::createEnumeration<cap>(values, currIndex, defIndex), 0);
    }


    /// Creates capability holding Range container.
    /// \param min Minimal range value.
    /// \param max Maximal range value.
    /// \param step Size of a single step.
    /// \param curr Current value.
    /// \param def Default value.
    /// \throw std::bad_alloc
    static Cap createRange(DataType min, DataType max, DataType step, DataType curr, DataType def){
        return Cap(Capability::createRange<cap>(min, max, step, curr, def), 0);
    }

    /// Creates capability of the supplied type without any data.
    /// Useful for retrieving data from data source.
    Cap() noexcept : m_cap(cap){}

    /// Converts Capability to Cap.
    /// The capability ownership is taken over.
    /// Capability type and item type checkings are performed. In case of exception,
    /// the original Capability instance may be retrieved from the exception object.
    /// \param capability Capability to be converted to Cap.
    /// \throw CapTypeException When input capability type does not match the
    ///                         capability type of this template class.
    /// \throw CapItemTypeException When input capability item type does not match
    ///                             the expected item type of the capability.
    explicit Cap(Capability capability) :
        m_cap(std::move(capability)){

        checkTypes();
    }

    Cap(Cap&&) = default;
    Cap& operator=(Cap&&) = default;

    Cap(const Cap&) = delete;
    Cap& operator=(const Cap&) = delete;

    /// Capability type.
    CapType type() const noexcept{
        return m_cap.type();
    }

    /// Container type.
    ConType container() const noexcept{
        return m_cap.container();
    }

    /// Item type.
    /// Valid only if the capability contains data.
    /// \throw DataException When there is no data.
    Type itemType() const{
        return m_cap.itemType();
    }

    operator bool() const noexcept{
        return m_cap;
    }

    /// Contained OneValue container.
    /// \throw DataException When there is no data.
    /// \throw ContainerException When container is not OneValue.
    /// \throw ItemTypeException When item type does not match.
    OneValue<twty, DataType> oneValue(){
        return m_cap.oneValue<cap>();
    }

    /// Contained Array container.
    /// \throw DataException When there is no data.
    /// \throw ContainerException When container is not Array.
    /// \throw ItemTypeException When item type does not match.
    Array<twty, DataType> array(){
        return m_cap.array<cap>();
    }

    /// Contained Enumeration container.
    /// \throw DataException When there is no data.
    /// \throw ContainerException When container is not Enumeration.
    /// \throw ItemTypeException When item type does not match.
    Enumeration<twty, DataType> enumeration(){
        return m_cap.enumeration<cap>();
    }

    /// Contained Range container.
    /// \throw DataException When there is no data.
    /// \throw ContainerException When container is not Enumeration.
    /// \throw ItemTypeException When item type does not match.
    Range<twty, DataType> range(){
        return m_cap.range<cap>();
    }


    typedef Detail::CapData<twty, DataType> Data;

    /// Returns a data container for iterating over all possible values.
    /// Use this only if you don't care about current or default values and container type.
    /// \throw DataException When there is no data.
    /// \throw ContainerException When container is invalid.
    /// \throw ItemTypeException When item type does not match.
    Data data() const{
        return m_cap.data<cap>();
    }


    /// Returns a copy of the current item of this capability.
    /// Can be used only with Enumeration, OneValue, and Range containers.
    /// \throw DataException When there is no data.
    /// \throw ContainerException When container is not Enumeration, OneValue, nor Range.
    /// \throw ItemTypeException When item type does not match.
    DataType currentItem(){
        return m_cap.currentItem<cap>();
    }

    /// Moves out the contained Capability instance.
    /// This instance becomes empty.
    Capability toCapability() noexcept{
        return std::move(m_cap);
    }

private:
    Cap(Capability capability, int) noexcept :
        m_cap(std::move(capability)){}

    void checkTypes(){
        if (m_cap){
            if (m_cap.type() != cap){
                throw CapTypeException(std::move(m_cap));
            }

            if (m_cap.itemType() != twty){
                throw CapItemTypeException(std::move(m_cap));
            }
        }
    }

    Capability m_cap;

};


namespace Detail {

/// \throw DataException
/// \throw ContainerException
/// \throw ItemTypeException
template<Type type, bool numeric, typename DataType> // numeric = false
inline CapDataImpl<type, numeric, DataType>::CapDataImpl(const Capability& cap) :
    m_conType(cap.m_conType), m_data(cap.m_cont.get()){

    static_assert(type != Type::DontCare, "type may not be DontCare");
    static_assert(sizeof(typename Detail::Twty<type>::Type) == sizeof(DataType), "type sizes dont match");

    if (!cap.m_cont){
        throw DataException();
    }

    switch (m_conType){
        case ConType::Array:
        case ConType::Enumeration:
        case ConType::OneValue:
            break;
        case ConType::Range:
        default:
            throw ContainerException();
    }

    if (type != cap.itemType()){
        throw ItemTypeException();
    }
}

/// \throw DataException
/// \throw ContainerException
/// \throw ItemTypeException
template<Type type, typename DataType>
inline CapDataImpl<type, true, DataType>::CapDataImpl(const Capability& cap) :
    m_conType(cap.m_conType), m_data(cap.m_cont.get()){

    static_assert(type != Type::DontCare, "type may not be DontCare");
    static_assert(sizeof(typename Detail::Twty<type>::Type) == sizeof(DataType), "type sizes dont match");

    if (!cap.m_cont){
        throw DataException();
    }

    switch (m_conType){
        case ConType::Array:
        case ConType::Enumeration:
        case ConType::OneValue:
        case ConType::Range:
            break;
        default:
            throw ContainerException();
    }

    if (type != cap.itemType()){
        throw ItemTypeException();
    }
}

/// \throw DataException
/// \throw ContainerException
/// \throw ItemTypeException
template<Type type, typename DataType, bool isNumeric> // false
DataType CurrentItemImpl<type, DataType, isNumeric>::item(Capability& cap){
    switch (cap.container()){
        case ConType::Enumeration:
            return cap.enumeration<type, DataType>().currentItem();

        case ConType::OneValue:
            return cap.oneValue<type, DataType>().item();

        default:
            throw ContainerException();
    }
}

/// \throw DataException
/// \throw ContainerException
/// \throw ItemTypeException
template<Type type, typename DataType>
DataType CurrentItemImpl<type, DataType, true>::item(Capability& cap){
    switch (cap.container()){
        case ConType::Enumeration:
            return cap.enumeration<type, DataType>().currentItem();

        case ConType::OneValue:
            return cap.oneValue<type, DataType>().item();

        case ConType::Range:
            return cap.range<type, DataType>().currentValue();

        default:
            throw ContainerException();
    }
}

}

}

#endif // TWPP_DETAIL_FILE_CAPABILITY_HPP

