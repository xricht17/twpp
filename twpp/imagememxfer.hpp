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

#ifndef TWPP_DETAIL_FILE_IMAGEMEMXFER_HPP
#define TWPP_DETAIL_FILE_IMAGEMEMXFER_HPP

#include "../twpp.hpp"

namespace Twpp {

TWPP_DETAIL_PACK_BEGIN
namespace Detail {

/// Structure holding the information and data of memory and memory file transfers.
class ImageMemXferImpl {

public:
    /// Creates a zero-initialized structure without any memory.
    constexpr ImageMemXferImpl() noexcept :
        m_compression(Compression::None), m_bytesPerRow(0), m_columns(0), m_rows(0),
        m_xoff(0), m_yoff(0), m_bytesWritten(0){}

    /// Creates an initialized structure from the supplied values and memory.
    /// The ownership of the memory is taken over.
    ImageMemXferImpl(
            Compression compression,
            UInt32 bytesPerRow,
            UInt32 columns,
            UInt32 rows,
            UInt32 xOffset,
            UInt32 yOffset,
            UInt32 bytesWritten,
            Memory memory
    ) noexcept :
        m_compression(compression), m_bytesPerRow(bytesPerRow),
        m_columns(columns), m_rows(rows), m_xoff(xOffset), m_yoff(yOffset),
        m_bytesWritten(bytesWritten), m_memory(std::move(memory)){}

    /// Compression used in the transfer.
    Compression compression() const noexcept{
        return m_compression;
    }

    /// Sets compression used in the transfer.
    void setCompression(Compression compression) noexcept{
        m_compression = compression;
    }

    /// Number of bytes per single row.
    UInt32 bytesPerRow() const noexcept{
        return m_bytesPerRow;
    }

    /// Sets number of bytes per single row.
    void setBytesPerRow(UInt32 bytesPerRow) noexcept{
        m_bytesPerRow = bytesPerRow;
    }

    /// Number of columns in the transfer.
    UInt32 columns() const noexcept{
        return m_columns;
    }

    /// Sets number of columns in the transfer.
    void setColumns(UInt32 columns) noexcept{
        m_columns = columns;
    }

    /// Number of rows in the transfer.
    UInt32 rows() const noexcept{
        return m_rows;
    }

    /// Sets number of rows in the transfer.
    void setRows(UInt32 rows) noexcept{
        m_rows = rows;
    }

    /// X offset from top-left corner in pixels of the image data in the transfer.
    UInt32 xOffset() const noexcept{
        return m_xoff;
    }

    /// Sets X offset from top-left corner in pixels of the image data in the transfer.
    void setXOffset(UInt32 xOffset) noexcept{
        m_xoff = xOffset;
    }

    /// Y offset from top-left corner in pixels of the image data in the transfer.
    UInt32 yOffset() const noexcept{
        return m_yoff;
    }

    /// Sets Y offset from top-left corner in pixels of the image data in the transfer.
    void setYOffset(UInt32 yOffset) noexcept{
        m_yoff = yOffset;
    }

    /// Number of bytes in this transfer, always contains whole rows or tiles.
    UInt32 bytesWritten() const noexcept{
        return m_bytesWritten;
    }

    /// Sets number of bytes in this transfer.
    void setBytesWritten(UInt32 bytesWritten) noexcept{
        m_bytesWritten = bytesWritten;
    }

    /// Contained memory structure.
    const Memory& memory() const noexcept{
        return m_memory;
    }

    /// Contained memory structure.
    Memory& memory() noexcept{
        return m_memory;
    }

private:
    Compression m_compression;
    UInt32 m_bytesPerRow;
    UInt32 m_columns;
    UInt32 m_rows;
    UInt32 m_xoff;
    UInt32 m_yoff;
    UInt32 m_bytesWritten;
    Memory m_memory;

};

}

/// Structure holding the information and data of memory transfer.
class ImageMemXfer : public Detail::ImageMemXferImpl {

public:
    /// Creates a zero-initialized structure without any memory.
    constexpr ImageMemXfer() noexcept : Detail::ImageMemXferImpl(){}

    /// Creates an initialized structure from the supplied values and memory.
    /// The ownership of the memory is taken over.
    ImageMemXfer(
            Compression compression,
            UInt32 bytesPerRow,
            UInt32 columns,
            UInt32 rows,
            UInt32 xOffset,
            UInt32 yOffset,
            UInt32 bytesWritten,
            Memory memory
    ) noexcept : Detail::ImageMemXferImpl(
        compression, bytesPerRow, columns, rows, xOffset,
        yOffset, bytesWritten, std::move(memory)){}

};

/// Structure holding the information and data of memory file transfer.
class ImageMemFileXfer : public Detail::ImageMemXferImpl {

public:
    /// Creates a zero-initialized structure without any memory.
    constexpr ImageMemFileXfer() noexcept : Detail::ImageMemXferImpl(){}

    /// Creates an initialized structure from the supplied values and memory.
    /// The ownership of the memory is taken over.
    ImageMemFileXfer(
            Compression compression,
            UInt32 bytesPerRow,
            UInt32 columns,
            UInt32 rows,
            UInt32 xOffset,
            UInt32 yOffset,
            UInt32 bytesWritten,
            Memory memory
    ) noexcept : Detail::ImageMemXferImpl(
        compression, bytesPerRow, columns, rows, xOffset,
        yOffset, bytesWritten, std::move(memory)){}

};
TWPP_DETAIL_PACK_END

}

#endif // TWPP_DETAIL_FILE_IMAGEMEMXFER_HPP
