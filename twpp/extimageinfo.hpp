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

#ifndef TWPP_DETAIL_FILE_EXTIMAGEINFO_HPP
#define TWPP_DETAIL_FILE_EXTIMAGEINFO_HPP

#include "../twpp.hpp"

namespace Twpp {

namespace Detail {

/// Mapping of info type to type identifier and data type.
template<InfoId id> struct Ext {};
template<> struct Ext<InfoId::BarCodeCount> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::BarCodeConfidence> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::BarCodeRotation> {static constexpr const Type twty = Type::UInt32; typedef BarCodeRotation DataType;};
template<> struct Ext<InfoId::BarCodeTextLength> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::BarCodeText> {static constexpr const Type twty = Type::Handle; typedef char DataType;};
template<> struct Ext<InfoId::BarCodeX> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::BarCodeY> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::BarCodeType> {static constexpr const Type twty = Type::UInt32; typedef BarCodeType DataType;};

template<> struct Ext<InfoId::DeShadeCount> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::DeShadeTop> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::DeShadeLeft> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::DeShadeHeight> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::DeShadeWidth> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::DeShadeSize> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::DeShadeBlackCountOld> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::DeShadeBlackCountNew> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::DeShadeBlackRlMin> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::DeShadeBlackRlMax> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::DeShadeWhiteCountOld> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::DeShadeWhiteCountNew> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::DeShadeWhiteRlMin> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::DeShadeWhiteRlMax> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::DeShadEWhiteRlAve> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};

template<> struct Ext<InfoId::SpecklesRemoved> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::BlackSpecklesRemoved> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::WhiteSpecklesRemoved> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};

template<> struct Ext<InfoId::HorzLineCount> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::HorzLineXCoord> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::HorzLineYCoord> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::HorzLineLength> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::HorzLineThickness> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};

template<> struct Ext<InfoId::VertLineCount> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::VertLineXCoord> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::VertLineYCoord> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::VertLineLength> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::VertLineThickness> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};

template<> struct Ext<InfoId::PatchCode> {static constexpr const Type twty = Type::UInt32; typedef PatchCode DataType;};

template<> struct Ext<InfoId::DeskewStatus> {static constexpr const Type twty = Type::UInt32; typedef DeskewStatus DataType;};
template<> struct Ext<InfoId::SkewOriginalAngle> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::SkewFinalAngle> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::SkewConfidence> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::SkewWindowX1> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::SkewWindowY1> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::SkewWindowX2> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::SkewWindowY2> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::SkewWindowX3> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::SkewWindowY3> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::SkewWindowX4> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::SkewWindowY4> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};

template<> struct Ext<InfoId::EndorsedText> {static constexpr const Type twty = Type::Str255; typedef Str255 DataType;};

template<> struct Ext<InfoId::FormConfidence> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::FormTemplateMatch> {static constexpr const Type twty = Type::Str255; typedef Str255 DataType;};
template<> struct Ext<InfoId::FormTemplatePageMatch> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::FormHorzDocOffset> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::FormVertDocOffset> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};

template<> struct Ext<InfoId::BookName> {static constexpr const Type twty = Type::Str255; typedef Str255 DataType;};
template<> struct Ext<InfoId::ChapterNumber> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::DocumentNumber> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::PageNumber> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::Camera> {static constexpr const Type twty = Type::Str255; typedef Str255 DataType;};
template<> struct Ext<InfoId::FrameNumber> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::Frame> {static constexpr const Type twty = Type::Frame; typedef Frame DataType;};
template<> struct Ext<InfoId::PixelFlavor> {static constexpr const Type twty = Type::UInt16; typedef PixelFlavor DataType;};

template<> struct Ext<InfoId::IccProfile> {static constexpr const Type twty = Type::Str255; typedef Str255 DataType;};
template<> struct Ext<InfoId::LastSegment> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Ext<InfoId::SegmentNumber> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};

template<> struct Ext<InfoId::MagType> {static constexpr const Type twty = Type::UInt16; typedef MagType DataType;};

template<> struct Ext<InfoId::FileSystemSource> {static constexpr const Type twty = Type::Str255; typedef Str255 DataType;};
template<> struct Ext<InfoId::ImageMerged> {static constexpr const Type twty = Type::Bool; typedef Bool DataType;};
template<> struct Ext<InfoId::MagData> {static constexpr const Type twty = Type::Str255; typedef char DataType;}; // NOTE: InfoId::MagData may also contain Handle
template<> struct Ext<InfoId::MagDataLength> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};
template<> struct Ext<InfoId::PageSide> {static constexpr const Type twty = Type::UInt16; typedef PageSide DataType;};

template<> struct Ext<InfoId::PaperCount> {static constexpr const Type twty = Type::UInt32; typedef UInt32 DataType;};

template<> struct Ext<InfoId::PrinterText> {static constexpr const Type twty = Type::Str255; typedef Str255 DataType;};

}

class Info;
class ExtImageInfo;

namespace Detail {

static Handle handleItem(Info& info) noexcept;

static void deleteInfo(Info& info) noexcept;

}

TWPP_DETAIL_PACK_BEGIN
/// Extended image information entry.
class Info {

    friend class ExtImageInfo;
    friend Handle Detail::handleItem(Info& info) noexcept;
    friend void Detail::deleteInfo(Info& info) noexcept;
    static constexpr const UInt32 DATA_HANDLE_THRESHOLD = sizeof(UIntPtr);  // NOTE: specification says 4 bytes, yet pointer size makes more sense

public:
    template<typename DataType>
    class Items {

        friend class Info;

    public:
        typedef Detail::MaybeLock<DataType> Data;

        constexpr Items() noexcept :
            m_parent(nullptr){}

        Items(const Items&) = default;
        Items& operator=(const Items&) = default;

        Items(Items&&) = default;
        Items& operator=(Items&&) = default;

        operator bool() const noexcept{
            return m_data;
        }

        Data at(UInt32 i) const{
            if (m_parent->hasDataHandle() && m_parent->type() == Type::Handle){
                return reinterpret_cast<Handle*>(m_data.data())[i];
            } else {
                return reinterpret_cast<DataType*>(m_data.data() + i * typeSize(m_parent->type()));
            }
        }

        Data operator[](UInt32 i) const{
            return at(i);
        }

    private:
        Items(Info& parent, Detail::MaybeLock<char> data) noexcept :
            m_parent(&parent), m_data(data){}

        Info* m_parent;
        Detail::MaybeLock<char> m_data;
            // [items] <=> !(big and handle)
            // [handles]->handles*[items] <=> big and handle (this should teoretically not happen)

    };

    Info(const Info&) = delete;
    Info& operator=(const Info&) = delete;

    Info(Info&&) = delete;
    Info& operator=(Info&&) = delete;

    /// Information type ID.
    InfoId id() const noexcept{
        return m_infoId;
    }

    /// Information data type ID.
    Type type() const noexcept{
        return m_itemType;
    }

    /// Number of items in this entry.
    UInt16 size() const noexcept{
        return m_numItems;
    }

    /// Allocates space for the supplied number of items.
    /// Allocating handles is not supported.
    /// \tparam id Information type ID. Data types are set accordingly.
    /// \param count Number of items to allocate.
    /// \throw std::invalid_argument On handle or invalid type.
    /// \throw std::bad_alloc
    template<InfoId id>
    void allocSimple(UInt16 count = 1){
        allocSimple(Detail::Ext<id>::twty, count);
    }

    /// Allocates space for the supplied number of items.
    /// Allocating handles is not supported.
    /// \param type Data type ID.
    /// \param count Number of items to allocate.
    /// \throw std::invalid_argument On handle or invalid type.
    /// \throw std::bad_alloc
    void allocSimple(Type type, UInt16 count = 1){
        if (type == Type::Handle){
            throw std::invalid_argument("handle items not supported");
        }

        if (type == m_itemType && count == m_numItems){
            return;
        }

        auto itemSize = typeSize(type);

        Detail::deleteInfo(*this);
        m_itemType = Type::DontCare;
        m_numItems = 0;

        bool big = hasDataHandle(type, count);

        // [items] <=> !big
        // handle->[items] <=> big

        if (big){
            *Detail::alias_cast<Handle*>(&m_item) = Detail::alloc(itemSize * count);
        }

        m_itemType = type;
        m_numItems = count;
    }

    /// Allocates a single memory area owned by a handle.
    /// Info type changes to handle.
    /// \param itemSize Number of bytes to allocate.
    /// \throw std::bad_alloc
    void allocHandle(UInt32 itemSize){
        Detail::deleteInfo(*this);

        m_itemType = Type::DontCare;
        m_numItems = 0;

        // handle->[chars]

        *Detail::alias_cast<Handle*>(&m_item) = Detail::alloc(itemSize);

        m_itemType = Type::Handle;
        m_numItems = 1;
    }

    /// Status of this entry.
    ReturnCode returnCode() const noexcept{
        return m_returnCode;
    }

    /// Sets status of this entry.
    void setReturnCode(ReturnCode rc) noexcept{
        m_returnCode = rc;
    }

    /// Returns items contained in this entry.
    /// \tparam type ID of the internal data type.
    /// \tparam DataType Exported data type.
    /// \throw std::invalid_argument When types don't match.
    template<Type type, typename DataType = typename Detail::Twty<type>::Type>
    Items<DataType> items(){
        if (type != m_itemType){
            throw std::invalid_argument("incorrect type");
        }

        return itemsPriv<DataType>();
    }

    /// Returns items contained in this entry.
    /// \tparam id Information type ID. Data types are set accordingly.
    /// \throw std::invalid_argument When types don't match.
    template<InfoId id>
    Items<typename Detail::Ext<id>::DataType> items(){
        if (Detail::Ext<id>::twty != m_itemType){
            throw std::invalid_argument("incorrect type");
        }

        return itemsPriv<typename Detail::Ext<id>::DataType>();
    }

private:
    bool hasDataHandle() const{
        return hasDataHandle(type(), size());
    }

    static bool hasDataHandle(Type type, UInt16 size){
        return type != Type::DontCare && size * typeSize(type) > DATA_HANDLE_THRESHOLD;
    }

    template<typename DataType>
    Items<DataType> itemsPriv(){
        bool big = hasDataHandle();
        bool handle = m_itemType == Type::Handle;

        Detail::MaybeLock<char> lock;
        if (!big && !handle){
            lock = Detail::alias_cast<char*>(&m_item);
        } else {
            lock = *Detail::alias_cast<Handle*>(&m_item);
        }

        return {*this, std::move(lock)};
    }

    template<typename T, std::size_t len>
    static bool arrContains(const T(& arr)[len], const T& val) noexcept{
        for (std::size_t i = 0; i < len; i++){
            if (arr[i] == val){
                return true;
            }
        }

        return false;
    }

    InfoId m_infoId;
    Type m_itemType;
    UInt16 m_numItems;
    ReturnCode m_returnCode;
    UIntPtr m_item;
        // [items] <=> !big and !handle
        // handle->[items] <=> big xor handle
        // handle->[handles]->handles*[items] <=> big and handle (this should teoretically not happen)

};

namespace Detail {

static inline Handle handleItem(Info& info) noexcept{
    return Handle(*Detail::alias_cast<Handle::Raw*>(&info.m_item));
}

static inline void deleteInfo(Info& info) noexcept{
    bool big = isType(info.type()) && info.hasDataHandle();
    bool handle = info.type() == Type::Handle;

    // [items] <=> !big and !handle
    // handle->[items] <=> big xor handle
    // handle->[handles]->handles*[items] <=> big and handle (this should teoretically not happen)

    if (big && handle){
        Detail::Lock<Handle> lock(handleItem(info));
        for (UInt16 i = 0; i < info.size(); i++){
            Detail::free(lock.data()[i]);
        }
    }

    if (big || handle){
        Detail::free(handleItem(info));
    }
}

struct ExtImageInfoData {
    UInt32 m_numInfos;
    Info m_infos[1];
};

}

TWPP_DETAIL_PACK_END
/// Extended image information.
/// Application sends list of info IDs,
/// source sets their data.
class ExtImageInfo {

public:
    typedef Info* iterator;
    typedef const Info* const_iterator;

    /// Creates an invalid object.
    ExtImageInfo() noexcept {}

    /// Creates a new structure for all supplied info IDs.
    /// Sources must not call this constructor, they
    /// are required to fill data in existing instance.
    /// \param ids List of requested info IDs to be filled in by the source.
    ExtImageInfo(std::initializer_list<InfoId> ids) :
        m_data(new char[sizeof(Detail::ExtImageInfoData) - sizeof(Info) + ids.size() * sizeof(Info)]()){

        ptr()->m_numInfos = ids.size();

        Info* infos = ptr()->m_infos;

        UInt32 i = 0;
        for (auto id : ids){
            auto& info = infos[i];
            i++;

            info.m_infoId = id;
            info.m_itemType = Type::DontCare;
        }
    }

    ExtImageInfo(ExtImageInfo&&) = default;
    ExtImageInfo& operator=(ExtImageInfo&&) = default;

    operator bool() const noexcept{
        return m_data.get() != nullptr;
    }

    /// Number of requested entries.
    UInt32 size() const noexcept{
        return ptr()->m_numInfos;
    }

    /// Information entry.
    Info& at(UInt32 i) noexcept{
        return ptr()->m_infos[i];
    }

    /// Information entry.
    const Info& at(UInt32 i) const noexcept{
        return ptr()->m_infos[i];
    }

    Info& operator[](UInt32 i) noexcept{
        return at(i);
    }

    const Info& operator[](UInt32 i) const noexcept{
        return at(i);
    }


    iterator begin() noexcept{
        return ptr()->m_infos;
    }

    const_iterator begin() const noexcept{
        return cbegin();
    }

    const_iterator cbegin() const noexcept{
        return ptr()->m_infos;
    }

    iterator end() noexcept{
        return ptr()->m_infos + ptr()->m_numInfos;
    }

    const_iterator end() const noexcept{
        return cend();
    }

    const_iterator cend() const noexcept{
        return ptr()->m_infos + ptr()->m_numInfos;
    }

private:
    Detail::ExtImageInfoData* ptr() noexcept{
        return reinterpret_cast<Detail::ExtImageInfoData*>(m_data.get());
    }

    Detail::ExtImageInfoData* ptr() const noexcept{
        return reinterpret_cast<Detail::ExtImageInfoData*>(m_data.get());
    }

    struct Deleter {
        void operator()(char* ptr) noexcept{
            Detail::ExtImageInfoData* data = reinterpret_cast<Detail::ExtImageInfoData*>(ptr);
            if (data){
                for (UInt32 i = 0; i < data->m_numInfos; i++){
                    Detail::deleteInfo(data->m_infos[i]);
                }

                delete [] ptr;
            }
        }
    };

    std::unique_ptr<char[], Deleter> m_data;

};

}

#endif // TWPP_DETAIL_FILE_EXTIMAGEINFO_HPP

