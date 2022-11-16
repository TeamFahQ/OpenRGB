/*-----------------------------------------*\
|  AsusCerberusKeyboardController.h         |
|                                           |
|  Definitions and types for ASUS Cerberus  |
|  USB RGB lighting controller              |
|                                           |
|  Mola19 03/03/2021                        |
\*-----------------------------------------*/

#include "RGBController.h"

#include <string>
#include <vector>
#include <hidapi/hidapi.h>

#pragma once

enum
{
    CERBERUS_KEYBOARD_MODE_STATIC       = 0,
    CERBERUS_KEYBOARD_MODE_BREATHING    = 1,
    CERBERUS_KEYBOARD_MODE_REACTIVE     = 2,
    CERBERUS_KEYBOARD_MODE_EXPLOSION    = 3,
    CERBERUS_KEYBOARD_MODE_COLOR_CYCLE  = 4,
    CERBERUS_KEYBOARD_MODE_WAVE         = 6,
    CERBERUS_KEYBOARD_MODE_CUSTOM       = 7,
};


class AsusCerberusKeyboardController
{
public:
    AsusCerberusKeyboardController(hid_device* dev_handle, const char* path, unsigned short rev_version);
    ~AsusCerberusKeyboardController();

    std::string GetDeviceLocation();
    std::string GetSerialString();
    std::string GetVersion();

    void SetProfile(uint8_t profile);
    void SetPerLEDColor(uint8_t key, uint8_t red, uint8_t green, uint8_t blue);
    void SendPerLEDColorEnd();
    void SetPerLEDMode(uint8_t mode);
    void SetMode(uint8_t mode, uint8_t red, uint8_t green, uint8_t blue, uint8_t direction, uint8_t brightness);


private:
    hid_device*                 dev;
    std::string                 location;
    unsigned short              version;
};
