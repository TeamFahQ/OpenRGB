/*-----------------------------------------*\
|  MSIMysticLight185Controller.h            |
|                                           |
|  Definitions and types for MSI Mystic     |
|   Light (185-byte) USB lighting           |
|   controllers                             |
|                                           |
|  T-bond 3/4/2020                          |
|  Adam Honse 3/6/2021                      |
\*-----------------------------------------*/

#include "MSIMysticLightCommon.h"
#include "RGBController.h"
#include <cstring>
#include <hidapi/hidapi.h>
#include <limits>

#pragma once

class MSIMysticLight185Controller
{
public:
    MSIMysticLight185Controller(hid_device* handle, const char *path);
    ~MSIMysticLight185Controller();

    unsigned int    GetZoneMinLedCount
                        (
                        MSI_ZONE        zone
                        );

    unsigned int    GetZoneMaxLedCount
                        (
                        MSI_ZONE        zone
                        );

    unsigned int    GetZoneLedCount
                        (
                        MSI_ZONE        zone
                        );

    void            SetZoneLedCount
                        (
                        MSI_ZONE        zone,
                        unsigned int    led_count
                        );

    void            SetMode
                        (
                        MSI_ZONE        zone,
                        MSI_MODE        mode,
                        MSI_SPEED       speed,
                        MSI_BRIGHTNESS  brightness,
                        bool            rainbow_color
                        );

    void            GetMode
                        (
                        MSI_ZONE        zone,
                        MSI_MODE        &mode,
                        MSI_SPEED       &speed,
                        MSI_BRIGHTNESS  &brightness,
                        bool            &rainbow_color
                        );

    void            SetZoneColor
                        (
                        MSI_ZONE        zone,
                        unsigned char   red1,
                        unsigned char   grn1,
                        unsigned char   blu1,
                        unsigned char   red2,
                        unsigned char   grn2,
                        unsigned char   blu2
                        );

    void            SetCycleCount
                        (
                        MSI_ZONE        zone,
                        unsigned char   cycle_num
                        );

    unsigned char   GetCycleCount
                        (
                        MSI_ZONE        zone
                        );

    std::pair<Color, Color>
                    GetZoneColor(MSI_ZONE zone);

    bool            Update();

    std::string     GetDeviceName();
    std::string     GetDeviceLocation();
    std::string     GetFWVersion();
    std::string     GetSerial();

private:
    bool            ReadSettings();
    void            SaveOnUpdate(bool send);
    bool            ReadFwVersion();
    void            ReadSerial();
    void            ReadName();
    ZoneData*       GetZoneData(MSI_ZONE zone);
    RainbowZoneData*
                    GetRainbowZoneData(MSI_ZONE zone);
    static unsigned char   BitSet(unsigned char value, bool bit, unsigned int position);

    hid_device*             dev;
    std::string             name;
    std::string             location;
    std::string             version_APROM;
    std::string             version_LDROM;
    std::string             chip_id;

    FeaturePacket_185       data;
};
