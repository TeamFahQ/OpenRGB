/*-----------------------------------*\
|  VS_XG270QG_Controller.cpp          |
|  Lanzaa 1/23/2022                   |
\*-----------------------------------*/

#include "VS_XG270QG_Controller.h"
#include "LogManager.h"

#include <cstring>

VS_XG270QG_Controller::VS_XG270QG_Controller(hid_device* device, const char* path)
{
    dev = device;
    location = path;
}

VS_XG270QG_Controller::~VS_XG270QG_Controller()
{
    hid_close(dev);
}

std::string VS_XG270QG_Controller::GetLocation()
{
    return location;
}

std::string VS_XG270QG_Controller::GetSerial()
{
    wchar_t serial_string[128];
    int ret = hid_get_serial_number_string(dev, serial_string, 128);

    if(ret != 0)
    {
        return("");
    }

    std::wstring return_wstring = serial_string;
    std::string return_string(return_wstring.begin(), return_wstring.end());

    return(return_string);
    return serial;
}

void VS_XG270QG_Controller::SetMode(uint8_t mode, uint8_t r, uint8_t g, uint8_t b)
{
    SendModeComplete(mode, r, g, b, mode, r, g, b);
}

void VS_XG270QG_Controller::SendModeComplete
    (
    uint8_t mode1, uint8_t r1, uint8_t g1, uint8_t b1,
    uint8_t mode2, uint8_t r2, uint8_t g2, uint8_t b2
    )
{
    uint8_t data[] = {
        0x02,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00,
        0x01,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    data[0x01] = mode1; // Downward facing LEDs
    data[0x02] = r1;
    data[0x03] = g1;
    data[0x04] = b1;
    data[0x05] = 0x00;
    data[0x06] = 0x0A;
    data[0x07] = 0x00;

    data[0x08] = mode2; // Back facing LEDs
    data[0x09] = r2;
    data[0x0A] = g2;
    data[0x0B] = b2;
    data[0x0C] = 0x00;
    data[0x0D] = 0x0A; // Might be speed related

    // original data packets are 0x40=64 long
    SendCommand(data, 0x20);
}

void VS_XG270QG_Controller::SendCommand(uint8_t  *data, size_t length)
{
    hid_send_feature_report(dev, data, length);
}

