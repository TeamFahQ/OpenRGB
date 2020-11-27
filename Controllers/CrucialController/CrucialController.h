/*-----------------------------------------*\
|  CrucialController.h                      |
|                                           |
|  Definitions and types for Crucial        |
|  Ballistix RGB lighting controller        |
|                                           |
|  Adam Honse (CalcProgrammer1) 1/19/2020   |
\*-----------------------------------------*/

#include "RGBController.h"
#include <string>
#include "i2c_smbus.h"

#pragma once

typedef unsigned char	crucial_dev_id;
typedef unsigned short	crucial_register;

enum
{
    CRUCIAL_MODE_UNKNOWN            = 0x00,     /* We don't know what the mode is   */
    CRUCIAL_MODE_SHIFT              = 0x1F,     /* Shift effect mode                */
    CRUCIAL_MODE_GRADIENT_SHIFT     = 0x2F,     /* Gradient shift mode              */
    CRUCIAL_MODE_FILL               = 0x3F,     /* Fill effect mode                 */
    CRUCIAL_MODE_STACK              = 0x4F,     /* Stack effect mode                */
    CRUCIAL_MODE_DOUBLE_STACK       = 0x5F,     /* Double stack effect mode         */
    CRUCIAL_MODE_BREATHING          = 0x6F,     /* Breathing effect mode            */
    CRUCIAL_MODE_MOTION_POINT       = 0x7F,     /* Motion point effect mode         */
    CRUCIAL_MODE_INSIDE_OUT         = 0x8F,     /* Inside out effect mode           */
    CRUCIAL_MODE_COLOR_STEP         = 0x9F,     /* Color step effect mode           */
    CRUCIAL_MODE_WATER_WAVE         = 0xAF,     /* Water wave effect mode           */
    CRUCIAL_MODE_FLASHING           = 0xBF,     /* Flashing effect mode             */
    CRUCIAL_MODE_STATIC             = 0xCF,     /* Static effect mode               */
};

class CrucialController
{
public:
    CrucialController(i2c_smbus_interface* bus, crucial_dev_id dev);
    ~CrucialController();

    std::string   GetDeviceName();
    std::string   GetDeviceLocation();
    unsigned int  GetLEDCount();
    void          SetAllColorsDirect(RGBColor* colors);
    void          SetAllColorsEffect(RGBColor* colors);
    void          SetMode(unsigned char mode);

    unsigned char CrucialRegisterRead(crucial_register reg);
    void          CrucialRegisterWrite(crucial_register reg, unsigned char val);

private:
    char                    device_name[16];
    unsigned char           config_table[64];
    unsigned int            led_count;
    unsigned char           channel_cfg;
    unsigned char           last_mode;
    i2c_smbus_interface *   bus;
    crucial_dev_id          dev;

    void            SendEffectColor
                        (
                        unsigned int    led_idx,
                        unsigned int    red,
                        unsigned int    green,
                        unsigned int    blue
                        );
    
    void            SendDirectColors(RGBColor* color_buf);
    void            SendBrightness(unsigned char brightness);
    void            SendEffectMode(unsigned char mode, unsigned char speed);
};
