/*-------------------------------------------*\
|  SinowealthGMOWController.h                 |
|                                             |
|  Support for the Glorious Model O Wireless  |
|                                             |
|  Matt Silva (thesilvanator) 05/2022         |
\*-------------------------------------------*/

#include "RGBController.h"
#include <vector>
#include <hidapi/hidapi.h>

#pragma once

#define GMOW_PACKET_SIZE 64 + 1

enum
{
    GMOW_MODE_OFF              = 0x00,
    GMOW_MODE_RAINBOW_WAVE     = 0x01,
    GMOW_MODE_SPECTRUM_CYCLE   = 0x02,
    GMOW_MODE_CUSTOM_BREATHING = 0x03,
    GMOW_MODE_STATIC           = 0x04,
    GMOW_MODE_BREATHING        = 0x05,
    GMOW_MODE_TAIL             = 0x06,
    GMOW_MODE_RAVE             = 0x07,
    GMOW_MODE_WAVE             = 0x08,
};

enum
{
    GMOW_SPEED1_MIN = 0x14,
    GMOW_SPEED1_MID = 0x0B,
    GMOW_SPEED1_MAX = 0x01,

    GMOW_SPEED2_MIN = 0xC8,
    GMOW_SPEED2_MID = 0x6E,
    GMOW_SPEED2_MAX = 0x0A,
};


enum
{
    GMOW_BRIGHTNESS_MIN = 0x00,
    GMOW_BRIGHTNESS_MID = 0x7F,
    GMOW_BRIGHTNESS_MAX = 0xFF,
};

enum
{
    GMOW_CABLE_CONNECTED,
    GMOW_DONGLE_CONNECTED
};


class SinowealthGMOWController
{
public:
    SinowealthGMOWController(hid_device* dev_handle, char *_path, int type);
    ~SinowealthGMOWController();

    std::string     GetLocation();
    std::string     GetSerialString();

    void            SetMode(unsigned char mode,
                            unsigned char speed,
                            unsigned char wired_brightness,
                            unsigned char less_brightness,
                            RGBColor* color_buf,
                            unsigned char color_count);

    std::string     GetFirmwareVersion();

private:
    hid_device*             dev;
    unsigned char           mode_packet[GMOW_PACKET_SIZE];
    unsigned char           wired_packet[GMOW_PACKET_SIZE];
    unsigned char           less_packet[GMOW_PACKET_SIZE];

    std::string             location;
    int                     type;
};
