/*-----------------------------------------*\
|  ZETEdgeAirProController.cpp              |
|                                           |
|  Driver for ZET Edge Air Pro mouse        |
|  lighting  controller                     |
|                                           |
|  Guimard Morgan (morg) 1/29/2022          |
\*-----------------------------------------*/
#include "ZETEdgeAirProController.h"
#include <string.h>

ZETEdgeAirProController::ZETEdgeAirProController(hid_device* dev_handle, const hid_device_info& info)
{
    dev                 = dev_handle;
    location            = info.path;
    version             = "";

    wchar_t serial_string[128];
    int ret = hid_get_serial_number_string(dev, serial_string, 128);

    if(ret != 0)
    {
        serial_number = "";
    }
    else
    {
        std::wstring return_wstring = serial_string;
        serial_number = std::string(return_wstring.begin(), return_wstring.end());
    }
}

ZETEdgeAirProController::~ZETEdgeAirProController()
{
    hid_close(dev);
}

std::string ZETEdgeAirProController::GetDeviceLocation()
{
    return("HID: " + location);
}

std::string ZETEdgeAirProController::GetSerialString()
{
    return(serial_number);
}

std::string ZETEdgeAirProController::GetFirmwareVersion()
{
    return(version);
}

void ZETEdgeAirProController::SetMode(RGBColor color, unsigned char brightness, unsigned char speed, unsigned char mode_value)
{
    /*---------------------------------------------------------*\
    | Init the packet buffer                                    |
    \*---------------------------------------------------------*/
    unsigned char usb_buf[ZET_EDGE_AIR_PRO_PACKET_SIZE];

    memset(usb_buf, 0x00, sizeof(usb_buf));

    /*---------------------------------------------------------*\œ
    | Constant data                                             |
    \*---------------------------------------------------------*/
    usb_buf[0x00] = ZET_EDGE_AIR_PRO_REPORT_ID;
    usb_buf[0x01] = 0x07;
    usb_buf[0x04] = 0xA0;
    usb_buf[0x05] = 0x07;

    /*---------------------------------------------------------*\
    | Set the mode                                              |
    \*---------------------------------------------------------*/
    usb_buf[0x06] = mode_value;

    /*---------------------------------------------------------*\
    | Set the color                                             |
    \*---------------------------------------------------------*/
    usb_buf[0x07] = RGBGetRValue(color);
    usb_buf[0x08] = RGBGetGValue(color);
    usb_buf[0x09] = RGBGetBValue(color);

    /*---------------------------------------------------------*\
    | Set speed if needed                                       |
    \*---------------------------------------------------------*/
    if(mode_value == BREATHING_MODE_VALUE)
    {
        unsigned char speed_values[ZET_EDGE_AIR_PRO_SPEED_MAX] =
        {
            0xFF,  0xE6, 0xD2, 0xBe, 0xAA, 0x96, 0x82, 0x6E, 0x46, 0x28
        };

        usb_buf[0x0A] = speed_values[speed - 1];
    }
    else if(mode_value == RAINBOW_MODE_VALUE)
    {
        unsigned char speed_values[ZET_EDGE_AIR_PRO_SPEED_MAX] =
        {
            0x2D,  0x28, 0x23, 0x1E, 0x19, 0x13, 0x0F, 0x0A, 0x05, 0x03
        };

        usb_buf[0x0A] = speed_values[speed - 1];
    }
    /*---------------------------------------------------------*\
    | Set brightness if needed                                  |
    \*---------------------------------------------------------*/
    if(mode_value != OFF_MODE_VALUE)
    {
        unsigned char brightness_values[ZET_EDGE_AIR_PRO_BRIGHTNESS_MAX] =
        {
            0x19,  0x32, 0x4B, 0x64, 0x7D, 0x96, 0xAF, 0xC8, 0xE1, 0xFF
        };

        usb_buf[0x0B] = brightness_values[brightness - 1];
    }

    /*---------------------------------------------------------*\
    | Custom CRC - thanks to Vaker for this <3                  |
    \*---------------------------------------------------------*/
    usb_buf[0x0C] = 0x55 - usb_buf[0x06] - usb_buf[0x07] - usb_buf[0x08] - usb_buf[0x09] - usb_buf[0x0A] - usb_buf[0x0B];

    /*---------------------------------------------------------*\
    | Constant data                                             |
    \*---------------------------------------------------------*/
    usb_buf[0x10] = ZET_EDGE_AIR_PRO_PACKET_END;

    /*---------------------------------------------------------*\
    | Send the report                                           |
    \*---------------------------------------------------------*/
    hid_send_feature_report(dev, usb_buf, ZET_EDGE_AIR_PRO_PACKET_SIZE);
}
