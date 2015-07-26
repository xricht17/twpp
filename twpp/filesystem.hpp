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

#ifndef TWPP_DETAIL_FILE_FILESYSTEM_HPP
#define TWPP_DETAIL_FILE_FILESYSTEM_HPP

#include "../twpp.hpp"

namespace Twpp {

TWPP_DETAIL_PACK_BEGIN
/// Structure representing device filesystem and operations on it.
class FileSystem {

public:
    /// Type of file.
    enum class Type : Int32 {
        Camera = 0,
        CameraTop = 1,
        CameraBottom = 2,
        CameraPreview = 3,
        Domain = 4,
        Host = 5,
        Directory = 6,
        Image = 7,
        Unknown = 8
    };

    /// Creates uninitialized file system.
    constexpr FileSystem() noexcept :
        m_context(nullptr), m_recursiveBool(), m_fileType(Type::Camera), m_size(),
        m_freeSpace(), m_newImageSize(), m_numberOfFiles(), m_numberOfSnippets(),
        m_deviceGroupMask(), m_reserved(){}

    /// Creates file system with input and output paths and optional context.
    constexpr FileSystem(const Str255& inputPath, const Str255& outputPath, void* context = nullptr) noexcept :
        m_inputPath(inputPath), m_outputPath(outputPath), m_context(context),
        m_recursiveBool(), m_fileType(Type::Camera), m_size(), m_freeSpace(), m_newImageSize(),
        m_numberOfFiles(), m_numberOfSnippets(), m_deviceGroupMask(), m_reserved(){}

    /// Input or source file.
    constexpr const Str255& inputPath() const noexcept{
        return m_inputPath;
    }

    /// Sets input or source file.
    void setInputPath(const Str255& path) noexcept{
        m_inputPath = path;
    }

    /// Operation result, or destination file.
    constexpr const Str255& outputPath() const noexcept{
        return m_outputPath;
    }

    /// Sets operation result, or destination file.
    void setOutputPath(const Str255& path) noexcept{
        m_outputPath = path;
    }

    /// Source specific context.
    constexpr void* context() const noexcept{
        return m_context;
    }

    /// Sets source specific context.
    void setContext(void* context) noexcept{
        m_context = context;
    }

    /// Whether the operation is recursive.
    /// Valid for Msg::GetInfo, Msg::GetFileFirst and Msg::Delete.
    constexpr Bool recursive() const noexcept{
        return m_recursiveBool;
    }

    /// Sets whether the operation is recursive.
    /// Valid for Msg::GetInfo, Msg::GetFileFirst and Msg::Delete.
    void setRecursive(Bool recursive) noexcept{
        m_recursiveBool = recursive;
    }

    /// File type.
    /// Valid for Msg::GetInfo, Msg::GetFileFirst and Msg::GetFileNext.
    constexpr Type type() const noexcept{
        return m_fileType;
    }

    /// Sets file type.
    /// Valid for Msg::GetInfo, Msg::GetFileFirst and Msg::GetFileNext.
    void setType(Type type) noexcept{
        m_fileType = type;
    }

    /// Number of bytes of the entry.
    /// Valid for Msg::GetInfo, Msg::GetFileFirst and Msg::GetFileNext.
    constexpr UInt32 size() const noexcept{
        return m_size;
    }

    /// Sets number of bytes of the entry.
    /// Valid for Msg::GetInfo, Msg::GetFileFirst and Msg::GetFileNext.
    void setSize(UInt32 size) noexcept{
        m_size = size;
    }

    /// Creation date of the file.
    /// Valid for Msg::GetInfo, Msg::GetFileFirst and Msg::GetFileNext.
    /// YYYY/MM/DD HH:mm:SS:sss
    constexpr const Str32& createdTimeDate() const noexcept{
        return m_createdTimeDate;
    }

    /// Sets creation date of the file.
    /// Valid for Msg::GetInfo, Msg::GetFileFirst and Msg::GetFileNext.
    /// YYYY/MM/DD HH:mm:SS:sss
    void setCreatedTimeDate(const Str32& val) noexcept{
        m_createdTimeDate = val;
    }

    /// Modification date of the file.
    /// Valid for Msg::GetInfo, Msg::GetFileFirst and Msg::GetFileNext.
    /// YYYY/MM/DD HH:mm:SS:sss
    constexpr const Str32& modifiedTimeDate() const noexcept{
        return m_modifiedTimeDate;
    }

    /// Sets modification date of the file.
    /// Valid for Msg::GetInfo, Msg::GetFileFirst and Msg::GetFileNext.
    /// YYYY/MM/DD HH:mm:SS:sss
    void setModifiedTimeDate(const Str32& val) noexcept{
        m_modifiedTimeDate = val;
    }

    /// Number of bytes left on the device.
    /// Valid for Msg::GetInfo, Msg::GetFileFirst and Msg::GetFileNext.
    constexpr UInt32 freeSpace() const noexcept{
        return m_freeSpace;
    }

    /// Sets number of bytes left on the device.
    /// Valid for Msg::GetInfo, Msg::GetFileFirst and Msg::GetFileNext.
    void setFreeSpace(UInt32 freeSpace) noexcept{
        m_freeSpace = freeSpace;
    }

    /// Estimated image size in bytes.
    /// Valid for Msg::GetInfo, Msg::GetFileFirst and Msg::GetFileNext.
    constexpr Int32 newImageSize() const noexcept{
        return m_newImageSize;
    }

    /// Sets estimated image size in bytes.
    /// Valid for Msg::GetInfo, Msg::GetFileFirst and Msg::GetFileNext.
    void setNewImageSize(Int32 newImageSize) noexcept{
        m_newImageSize = newImageSize;
    }

    /// Total number of files including subdirectories.
    /// Valid for Msg::GetInfo, Msg::GetFileFirst and Msg::GetFileNext.
    constexpr UInt32 files() const noexcept{
        return m_numberOfFiles;
    }

    /// Sets total number of files including subdirectories.
    /// Valid for Msg::GetInfo, Msg::GetFileFirst and Msg::GetFileNext.
    void setFiles(UInt32 files) noexcept{
        m_numberOfFiles = files;
    }

    /// Number of audio snippets.
    /// Valid for Msg::GetInfo, Msg::GetFileFirst and Msg::GetFileNext.
    constexpr UInt32 snippets() const noexcept{
        return m_numberOfSnippets;
    }

    /// Sets number of audio snippets.
    /// Valid for Msg::GetInfo, Msg::GetFileFirst and Msg::GetFileNext.
    void snippets(UInt32 snippets) noexcept{
        m_numberOfSnippets = snippets;
    }

    /// See manual for explanation of this field, `DeviceGroupMask`.
    constexpr UInt32 groupMask() const noexcept{
        return m_deviceGroupMask;
    }

    /// See manual for explanation of this field, `DeviceGroupMask`.
    void groupMask(UInt32 groupMask) noexcept{
        m_deviceGroupMask = groupMask;
    }

private:
    void unused() const{
        Detail::unused(m_reserved);
    }

    Str255 m_inputPath;
    Str255 m_outputPath;
    void* m_context;

    // Copy, Delete
    union {
        int m_recursive;
        Bool m_recursiveBool;
    };

    // GetInfo
    Type m_fileType;
    UInt32 m_size;
    Str32 m_createdTimeDate;
    Str32 m_modifiedTimeDate;
    UInt32 m_freeSpace;
    Int32 m_newImageSize;
    UInt32 m_numberOfFiles;
    UInt32 m_numberOfSnippets;
    UInt32 m_deviceGroupMask;
    Int8 m_reserved[508];

};
TWPP_DETAIL_PACK_END

}

#endif // TWPP_DETAIL_FILE_FILESYSTEM_HPP
