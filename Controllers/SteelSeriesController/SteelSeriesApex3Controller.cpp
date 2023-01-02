/*-------------------------------------------------------------------*\
|  SteelSeriesApex3Controller.cpp                                     |
|                                                                     |
|  Driver for Steelseries Apex3 Controllers                           |
|       This is the base class for the Ten Zone and 8 Zone keyboards  |
|                                                                     |
|  Chris M (Dr_No)          23rd Feb 2022                             |
\*-------------------------------------------------------------------*/

#include <cstring>
#include "SteelSeriesApex3Controller.h"

SteelSeriesApex3Controller::SteelSeriesApex3Controller(hid_device* dev_handle, const char* path)
{
    dev         = dev_handle;
    location    = path;
}

SteelSeriesApex3Controller::~SteelSeriesApex3Controller()
{
    hid_close(dev);
}

std::string SteelSeriesApex3Controller::GetDeviceLocation()
{
    return("HID: " + location);
}

std::string SteelSeriesApex3Controller::GetSerialString()
{
    wchar_t serial_string[128];
    int ret = hid_get_serial_number_string(dev, serial_string, 128);

    if (ret != 0)
    {
        return("");
    }

    std::wstring return_wstring = serial_string;
    std::string return_string(return_wstring.begin(), return_wstring.end());

    return(return_string);
}
