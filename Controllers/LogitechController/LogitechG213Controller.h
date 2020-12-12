/*-----------------------------------------*\
|  LogitechG213Controller.h                 |
|                                           |
|  Generic RGB Interface for Logitech G213  |
|                                           |
|  Eric Samuelson (edbgon) 10/06/2020       |
\*-----------------------------------------*/

#include "RGBController.h"

#include <string>
#include <hidapi/hidapi.h>

#pragma once

class LogitechG213Controller
{
public:
    LogitechG213Controller(hid_device* dev_handle, const char* path);
    ~LogitechG213Controller();

    std::string GetDeviceLocation();
    std::string GetSerialString();

    void        SetDirect
                    (
                    unsigned char       zone,
                    unsigned char       r,
                    unsigned char       g,
                    unsigned char       b
                    );

private:
    hid_device* dev;
    std::string location;

};
