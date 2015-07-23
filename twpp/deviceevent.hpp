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

#ifndef TWPP_DETAIL_FILE_DEVICEEVENT_HPP
#define TWPP_DETAIL_FILE_DEVICEEVENT_HPP

#include "../twpp.hpp"

namespace Twpp {

TWPP_DETAIL_PACK_BEGIN
/// Information about event sent by source.
class DeviceEvent {

public:
    /// Event type.
    enum class Type : UInt16 { // Capability->UInt16, DeviceEvent->UInt32
        CheckAutomaticCapture = 0,
        CheckBattery = 1,
        CheckDeviceOnline = 2,
        CheckFlash = 3,
        CheckPowerSupply = 4,
        CheckResolution = 5,
        DeviceAdded = 6,
        DeviceOffline = 7,
        DeviceReady = 8,
        DeviceRemoved = 9,
        ImageCaptured = 10,
        ImageDeleted = 11,
        PaperDoubleFeed = 12,
        PaperJam = 13,
        LampFailure = 14,
        PowerSave = 15,
        PowerSaveNotify = 16,
        CustomEvents = 0x8000
    };

    /// Creates event with only type and device name set.
    static constexpr DeviceEvent simple(Type type, const Str255& deviceName) noexcept{
        return DeviceEvent(type, deviceName, 0, 0, PowerSupply::External, Fix32(), Fix32(), Flash::None, 0, 0, 0);
    }

    /// Creates event for checking battery.
    static constexpr DeviceEvent checkBattery(
            const Str255& deviceName,
            UInt32 batteryMinutes,
            Int16 batteryPercentage
    ) noexcept{
        return DeviceEvent(Type::CheckBattery, deviceName, batteryMinutes, batteryPercentage, PowerSupply::External, Fix32(), Fix32(), Flash::None, 0, 0, 0);
    }

    /// Creates event for checking power supply.
    static constexpr DeviceEvent checkPowerSupply(
            const Str255& deviceName,
            PowerSupply powerSupply
    ) noexcept{
        return DeviceEvent(Type::CheckPowerSupply, deviceName, 0, 0, powerSupply, Fix32(), Fix32(), Flash::None, 0, 0, 0);
    }

    /// Creates event for checking resolution.
    static constexpr DeviceEvent checkResolution(
            const Str255& deviceName,
            Fix32 xres,
            Fix32 yres
    ) noexcept{
        return DeviceEvent(Type::CheckResolution, deviceName, 0, 0, PowerSupply::External, xres, yres, Flash::None, 0, 0, 0);
    }

    /// Creates event for checking flash settings.
    static constexpr DeviceEvent checkFlash(
            const Str255& deviceName,
            Flash flash
    ) noexcept{
        return DeviceEvent(Type::CheckFlash, deviceName, 0, 0, PowerSupply::External, Fix32(), Fix32(), flash, 0, 0, 0);
    }

    /// Creates event for checking number of images camera is going to capture.
    static constexpr DeviceEvent checkAutomaticCapture(
            const Str255& deviceName,
            UInt32 autoCapture,
            UInt32 timeBeforeFirstCapture,
            UInt32 timeBetweenCaptures
    ) noexcept{
        return DeviceEvent(Type::CheckAutomaticCapture, deviceName, 0, 0, PowerSupply::External,
                           Fix32(), Fix32(), Flash::None, autoCapture, timeBeforeFirstCapture, timeBetweenCaptures);
    }

    /// Creates uninitialized deice event.
    constexpr DeviceEvent() noexcept :
        m_type(static_cast<UInt32>(Type::CheckAutomaticCapture)), m_batteryMinutes(0),
        m_batteryPercent(0), m_powerSupply(static_cast<Int32>(PowerSupply::External)),
        m_flashUsed(static_cast<UInt32>(Flash::None)), m_autoCapture(0),
        m_timeBeforeFirstCapture(0), m_timeBetweenCaptures(0){}

    /// Event type.
    constexpr Type type() const noexcept{
        return static_cast<Type>(m_type);
    }

    /// Name of the device that sent the event.
    constexpr const Str255& deviceName() const noexcept{
        return m_deviceName;
    }

    /// Minutes of battery power remaining.
    /// Valid only for Type::CheckBattery.
    constexpr UInt32 batteryMinutes() const noexcept{
        return m_batteryMinutes;
    }

    /// Percentage of battery power remaining.
    /// Valid only for Type::CheckBattery.
    constexpr Int16 batteryPercentage() const noexcept{
        return m_batteryPercent;
    }

    /// Power supply in use.
    /// Valid only for Type::CheckPowerSupply.
    constexpr PowerSupply powerSupply() const noexcept{
        return static_cast<PowerSupply>(m_powerSupply);
    }

    /// X resolution.
    /// Valif only for Type::CheckResolution.
    constexpr Fix32 xResolution() const noexcept{
        return m_xres;
    }

    /// Y resolution.
    /// Valid only for Type::CheckResolution.
    constexpr Fix32 yResolution() const noexcept{
        return m_yres;
    }

    /// Flash settings.
    /// Valid only for Type::CheckFlash.
    constexpr Flash flash() const noexcept{
        return static_cast<Flash>(m_flashUsed);
    }

    /// Number of images camera will capture.
    /// Valid only for Type::CheckAutomaticCapture.
    constexpr UInt32 automaticCapture() const noexcept{
        return m_autoCapture;
    }

    /// Number of seconds before first capture.
    /// Valid only for Type::CheckAutomaticCapture.
    constexpr UInt32 timeBeforeFirstCapture() const noexcept{
        return m_timeBeforeFirstCapture;
    }

    /// Number of 1/100-seconds between captures.
    /// Valid only for Type::CheckAutomaticCapture.
    constexpr UInt32 timeBetweenCaptures() const noexcept{
        return m_timeBetweenCaptures;
    }

private:
    constexpr DeviceEvent(
            Type type,
            const Str255& deviceName,
            UInt32 batteryMinutes,
            Int16 batteryPercentage,
            PowerSupply powerSupply,
            Fix32 xres,
            Fix32 yres,
            Flash flash,
            UInt32 autoCapture,
            UInt32 tbfc,
            UInt32 tbc
    ) noexcept :
        m_type(static_cast<UInt32>(type)), m_deviceName(deviceName),
        m_batteryMinutes(batteryMinutes), m_batteryPercent(batteryPercentage),
        m_powerSupply(static_cast<Int32>(powerSupply)), m_xres(xres), m_yres(yres),
        m_flashUsed(static_cast<UInt32>(flash)), m_autoCapture(autoCapture),
        m_timeBeforeFirstCapture(tbfc), m_timeBetweenCaptures(tbc){}

    UInt32 m_type;
    Str255 m_deviceName;
    UInt32 m_batteryMinutes;
    Int16 m_batteryPercent;
    Int32 m_powerSupply;
    Fix32 m_xres;
    Fix32 m_yres;
    UInt32 m_flashUsed;
    UInt32 m_autoCapture;
    UInt32 m_timeBeforeFirstCapture;
    UInt32 m_timeBetweenCaptures;

};
TWPP_DETAIL_PACK_END

}

#endif // TWPP_DETAIL_FILE_DEVICEEVENT_HPP
