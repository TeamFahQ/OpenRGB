/*-----------------------------------------*\
|  RGBController_LogitechG303.cpp           |
|                                           |
|  Generic RGB Interface for Logitech G303  |
|  Daedalus Apex Mouse                      |
|                                           |
|  TheRogueZeta   02/14/2021                |
\*-----------------------------------------*/

#include "RGBController_LogitechG303.h"

RGBController_LogitechG303::RGBController_LogitechG303(LogitechG303Controller* logitech_ptr)
{
    logitech = logitech_ptr;

    name                            = "Logitech Mouse Device";
    type                            = DEVICE_TYPE_MOUSE;
    description                     = "Logitech Mouse Device";
    location                        = logitech->GetDeviceLocation();

    mode Off;
    Off.name                        = "Off";
    Off.value                       = LOGITECH_G303_MODE_OFF;
    Off.flags                       = 0;
    Off.color_mode                  = MODE_COLORS_NONE;
    modes.push_back(Off);

    mode Static;
    Static.name                     = "Static";
    Static.value                    = LOGITECH_G303_MODE_STATIC;
    Static.flags                    = MODE_FLAG_HAS_PER_LED_COLOR;
    Static.color_mode               = MODE_COLORS_PER_LED;
    modes.push_back(Static);

    mode Cycle;
    Cycle.name                      = "Cycle";
    Cycle.value                     = LOGITECH_G303_MODE_CYCLE;
    Cycle.flags                     = MODE_FLAG_HAS_SPEED;
    Cycle.color_mode                = MODE_COLORS_NONE;
    Cycle.speed_min                 = LOGITECH_G303_SPEED_SLOWEST;
    Cycle.speed_max                 = LOGITECH_G303_SPEED_FASTEST;
    Cycle.speed                     = LOGITECH_G303_SPEED_NORMAL;
    modes.push_back(Cycle);

    mode Breathing;
    Breathing.name                  = "Breathing";
    Breathing.value                 = LOGITECH_G303_MODE_BREATHING;
    Breathing.flags                 = MODE_FLAG_HAS_PER_LED_COLOR | MODE_FLAG_HAS_SPEED;
    Breathing.color_mode            = MODE_COLORS_PER_LED;
    Breathing.speed_min             = LOGITECH_G303_SPEED_SLOWEST;
    Breathing.speed_max             = LOGITECH_G303_SPEED_FASTEST;
    Breathing.speed                 = LOGITECH_G303_SPEED_NORMAL;
    modes.push_back(Breathing);

    SetupZones();
}

RGBController_LogitechG303::~RGBController_LogitechG303()
{
    delete logitech;
}

void RGBController_LogitechG303::SetupZones()
{
    zone G303_primary_zone;
    G303_primary_zone.name          = "Primary";
    G303_primary_zone.type          = ZONE_TYPE_SINGLE;
    G303_primary_zone.leds_min      = 1;
    G303_primary_zone.leds_max      = 1;
    G303_primary_zone.leds_count    = 1;
    G303_primary_zone.matrix_map    = NULL;
    zones.push_back(G303_primary_zone);

    led G303_primary_led;
    G303_primary_led.name = "Primary";
    leds.push_back(G303_primary_led);

    zone G303_logo_zone;
    G303_logo_zone.name             = "Logo";
    G303_logo_zone.type             = ZONE_TYPE_SINGLE;
    G303_logo_zone.leds_min         = 1;
    G303_logo_zone.leds_max         = 1;
    G303_logo_zone.leds_count       = 1;
    G303_logo_zone.matrix_map       = NULL;
    zones.push_back(G303_logo_zone);

    led G303_logo_led;
    G303_logo_led.name = "Logo";
    leds.push_back(G303_logo_led);

    SetupColors();
}

void RGBController_LogitechG303::ResizeZone(int /*zone*/, int /*new_size*/)
{
    /*---------------------------------------------------------*\
    | This device does not support resizing zones               |
    \*---------------------------------------------------------*/
}

void RGBController_LogitechG303::DeviceUpdateLEDs()
{
    UpdateZoneLEDs(0);
    UpdateZoneLEDs(1);
}

void RGBController_LogitechG303::UpdateZoneLEDs(int zone)
{
    unsigned char red = RGBGetRValue(colors[zone]);
    unsigned char grn = RGBGetGValue(colors[zone]);
    unsigned char blu = RGBGetBValue(colors[zone]);

    logitech->SendMouseMode(modes[active_mode].value, modes[active_mode].speed, zone, red, grn, blu);
}

void RGBController_LogitechG303::UpdateSingleLED(int led)
{
    UpdateZoneLEDs(led);
}

void RGBController_LogitechG303::SetCustomMode()
{

}

void RGBController_LogitechG303::DeviceUpdateMode()
{
    DeviceUpdateLEDs();
}
