/*-----------------------------------------*\
|  SteelSeriesRival3Controller.h            |
|                                           |
|  Definitions and types for SteelSeries    |
|  Rival 3 lighting controller              |
|                                           |
|  B Horn (bahorn) 29/8/2021                |
\*-----------------------------------------*/

#include <string>
#include <hidapi/hidapi.h>

#include "SteelSeriesGeneric.h"
#include "SteelSeriesMouseController.h"

#pragma once

//#define STEELSERIES_RIVAL_3_BRIGHTNESS_MAX          0x64

/*static const steelseries_mouse_led_info rival_3_leds[]=
{
    {"Front",           0x01},
    {"Middle",          0x02},
    {"Rear",            0x03},
    {"Logo",            0x04}
};*/

static const steelseries_mouse rival_3 =
{
    {   0x04, 0x03, 0x00, 0x05  },
    {
        {"Front",           0x01},
        {"Middle",          0x02},
        {"Rear",            0x03},
        {"Logo",            0x04}
    }
};

class SteelSeriesRival3Controller: public SteelSeriesMouseController
{
public:
    SteelSeriesRival3Controller
        (
        hid_device*         dev_handle,
        steelseries_type    proto_type,
        const char*         path
        );

    ~SteelSeriesRival3Controller();

    //std::string         GetDeviceLocation();
    //char*               GetDeviceName();
    //std::string         GetSerialString();
    std::string         GetFirmwareVersion();
    steelseries_mouse   GetMouse();
    //steelseries_type    GetMouseType();

    //void                Save();

    void                SetLightEffectAll(uint8_t effect);

    void                SetColor
                            (
                            unsigned char   zone_id,
                            unsigned char   red,
                            unsigned char   green,
                            unsigned char   blue,
                            unsigned char   brightness
                            );

private:
    //char                    device_name[32];
    //hid_device*             dev;
    //std::string             location;
    //steelseries_type        proto;
};
