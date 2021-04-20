/*-----------------------------------------*\
|  WootingKeyboardController.cpp            |
|                                           |
|  Driver for Wooting RGB keyboardlighting  |
|  controller                               |
|                                           |
|  Diogo Trindade (diogotr7)    3/4/2021    |
\*-----------------------------------------*/

#include <cstring>
#include "WootingKeyboardController.h"

#define WOOTING_COMMAND_SIZE            8
#define WOOTING_REPORT_SIZE             129
#define WOOTING_RAW_COLORS_REPORT       11
#define WOOTING_SINGLE_COLOR_COMMAND    30
#define WOOTING_SINGLE_RESET_COMMAND    31
#define WOOTING_RESET_ALL_COMMAND       32
#define WOOTING_COLOR_INIT_COMMAND      33
#define WOOTING_ONE_KEY_CODE_LIMIT      95
#define WOOTING_TWO_KEY_CODE_LIMIT      116
#define RGB_RAW_BUFFER_SIZE             96

//0xFFFFFFFF indicates an unused entry in matrix
#define NA 0xFFFFFFFF

static const unsigned int rgb_led_index[6][17] =
{
    {0,  NA, 11, 12, 23, 24, 36, 47, 85, 84, 49, 48, 59, 61, 73, 81, 80},
    {2,  1,  14, 13, 26, 25, 35, 38, 37, 87, 86, 95, 51, 63, 75, 72, 74},
    {3,  4,  15, 16, 27, 28, 39, 42, 40, 88, 89, 52, 53, 71, 76, 83, 77},
    {5,  6,  17, 18, 29, 30, 41, 46, 44, 90, 93, 54, 57, 65, NA, NA, NA},
    {9,  8,  19, 20, 31, 34, 32, 45, 43, 91, 92, 55, NA, 66, NA, 78, NA},
    {10, 22, 21, NA, NA, NA, 33, NA, NA, NA, 94, 58, 67, 68, 70, 79, 82}
};

static uint16_t getCrc16ccitt(const uint8_t* buffer, uint16_t size)
{
    uint16_t crc = 0;

    while(size--)
    {
        crc ^= (*buffer++ << 8);

        for(uint8_t i = 0; i < 8; ++i)
        {
            if(crc & 0x8000)
            {
                crc = (crc << 1) ^ 0x1021;
            }
            else
            {
                crc = crc << 1;
            }
        }
    }

    return crc;
}

WootingKeyboardController::WootingKeyboardController(hid_device* dev_handle)
{
    dev = dev_handle;

    SendInitialize();
}

WootingKeyboardController::~WootingKeyboardController()
{
    
}

void WootingKeyboardController::SendDirect(RGBColor* colors, unsigned int num_colors)
{
    const uint8_t pwm_mem_map[48] =
    {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D,
        0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D,
        0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D,
        0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D
    };

    unsigned char buffer0[RGB_RAW_BUFFER_SIZE] = {0};
    unsigned char buffer1[RGB_RAW_BUFFER_SIZE] = {0};
    unsigned char buffer2[RGB_RAW_BUFFER_SIZE] = {0};
    unsigned char buffer3[RGB_RAW_BUFFER_SIZE] = {0};

    for(std::size_t color_idx = 0; color_idx < num_colors; color_idx++)
    {
        unsigned char led_index = rgb_led_index[color_idx % 6][color_idx / 6];

        if(led_index > 95)
        {
            continue;
        }

        unsigned char *buffer_pointer = buffer0;

        if(led_index >= 72)
        {
            buffer_pointer = buffer3;
        }
        else if(led_index >= 48)
        {
            buffer_pointer = buffer2;
        }
        else if(led_index >= 24)
        {
            buffer_pointer = buffer1;
        }
        else
        {
            buffer_pointer = buffer0;
        }

        unsigned char buffer_index          = pwm_mem_map[led_index % 24];
        buffer_pointer[buffer_index + 0x00] = RGBGetRValue(colors[color_idx]);
        buffer_pointer[buffer_index + 0x10] = RGBGetGValue(colors[color_idx]);
        buffer_pointer[buffer_index + 0x20] = RGBGetBValue(colors[color_idx]);
    }

    wooting_usb_send_buffer(RGB_PARTS::PART0, buffer0);
    wooting_usb_send_buffer(RGB_PARTS::PART1, buffer1);
    wooting_usb_send_buffer(RGB_PARTS::PART2, buffer2);
    wooting_usb_send_buffer(RGB_PARTS::PART3, buffer3);
}

void WootingKeyboardController::SendInitialize()
{
    wooting_usb_send_feature(WOOTING_COLOR_INIT_COMMAND, 0,0,0,0);
    unsigned char stub = 0;
    hid_read(dev, &stub, 0);
    hid_read_timeout(dev, &stub, 0, 50);
}

bool WootingKeyboardController::wooting_usb_send_feature(uint8_t commandId, uint8_t parameter0, uint8_t parameter1, uint8_t parameter2, uint8_t parameter3)
{
    /*---------------------------------------------------------*\
    | Prevent sending unnecessary data to the Wootings if the   |
    | index exceedes it's capabilities                          |
    \*---------------------------------------------------------*/
    if ((commandId == WOOTING_SINGLE_COLOR_COMMAND && parameter0 > WOOTING_ONE_KEY_CODE_LIMIT)
     || (commandId == WOOTING_SINGLE_RESET_COMMAND && parameter3 > WOOTING_ONE_KEY_CODE_LIMIT))
    {
        /*-----------------------------------------------------*\
        | This is not a USB error so let's return true.         |
        | wooting_rgb_direct_set_key would also behave          |
        | differently otherwise.                                |
        \*-----------------------------------------------------*/
        return true;
    }

    unsigned char report_buffer[WOOTING_COMMAND_SIZE] = {0};

    /*---------------------------------------------------------*\
    | Set up the Send Feature packet                            |
    \*---------------------------------------------------------*/
    report_buffer[0] = 0;                           // HID report index (unused)
    report_buffer[1] = 0xD0;                        // Magic word
    report_buffer[2] = 0xDA;                        // Magic word
    report_buffer[3] = commandId;
    report_buffer[4] = parameter3;
    report_buffer[5] = parameter2;
    report_buffer[6] = parameter1;
    report_buffer[7] = parameter0;

    /*---------------------------------------------------------*\
    | Send packet                                               |
    \*---------------------------------------------------------*/
    hid_send_feature_report(dev, report_buffer, WOOTING_COMMAND_SIZE);
}

bool WootingKeyboardController::wooting_usb_send_buffer(RGB_PARTS part_number, uint8_t rgb_buffer[])
{
    unsigned char report_buffer[WOOTING_REPORT_SIZE] = {0};

    /*---------------------------------------------------------*\
    | Set up the Send Buffer packet                             |
    \*---------------------------------------------------------*/
    report_buffer[0] = 0;                           // HID report index (unused)
    report_buffer[1] = 0xD0;                        // Magic word
    report_buffer[2] = 0xDA;                        // Magic word
    report_buffer[3] = WOOTING_RAW_COLORS_REPORT;   // Report ID

    switch(part_number)
    {
        case PART0:
            report_buffer[4] = 0;                   // Slave nr
            report_buffer[5] = 0;                   // Reg start address
            break;

        case PART1:
            report_buffer[4] = 0;                   // Slave nr
            report_buffer[5] = RGB_RAW_BUFFER_SIZE; // Reg start address
            break;

        case PART2:
            report_buffer[4] = 1;                   // Slave nr
            report_buffer[5] = 0;                   // Reg start address
            break;

        case PART3:
            report_buffer[4] = 1;                   // Slave nr
            report_buffer[5] = RGB_RAW_BUFFER_SIZE; // Reg start address
            break;

        default:
            return false;
            break;
    }

    /*---------------------------------------------------------*\
    | Copy in the buffer data                                   |
    \*---------------------------------------------------------*/
    memcpy(&report_buffer[6], rgb_buffer, RGB_RAW_BUFFER_SIZE);

    /*---------------------------------------------------------*\
    | Calculate the CRC and append it to the packet             |
    \*---------------------------------------------------------*/
    unsigned short crc = getCrc16ccitt((unsigned char*)&report_buffer, WOOTING_REPORT_SIZE - 2);
    report_buffer[127] = (unsigned char)crc;
    report_buffer[128] = crc >> 8;

    /*---------------------------------------------------------*\
    | Send packet                                               |
    \*---------------------------------------------------------*/
    hid_write(dev, report_buffer, WOOTING_REPORT_SIZE);
}
