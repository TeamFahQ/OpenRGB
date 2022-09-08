#include "RGBController_CreativeSoundBlasterXG6.h"

/**------------------------------------------------------------------*\
    @name Creative Sound BlasterX G6
    @category Headset
    @type USB
    @save :x:
    @direct :white_check_mark:
    @effects :x:
    @detectors DetectCreativeDevice
    @comment
\*-------------------------------------------------------------------*/

RGBController_CreativeSoundBlasterXG6::RGBController_CreativeSoundBlasterXG6(CreativeSoundBlasterXG6Controller* controller_ptr)
{
    controller  = controller_ptr;

    name        = "Creative SoundBlasterX G6 Device";
    vendor      = "Creative";
    type        = DEVICE_TYPE_HEADSET;
    description = "Creative SoundBlasterX G6 Device";
    location    = controller->GetDeviceLocation();
    serial      = "";

    mode Static;
    Static.name                     = "Direct";
    Static.value                    = 0;
    Static.flags                    = MODE_COLORS_PER_LED;
    Static.color_mode               = MODE_COLORS_PER_LED;
    modes.push_back(Static);

    SetupZones();
}

RGBController_CreativeSoundBlasterXG6::~RGBController_CreativeSoundBlasterXG6()
{
    delete controller;
}

void RGBController_CreativeSoundBlasterXG6::SetupZones()
{
    zone logo_zone;
    logo_zone.name                  = "Logo";
    logo_zone.type                  = ZONE_TYPE_SINGLE;
    logo_zone.leds_min              = 1;
    logo_zone.leds_max              = 1;
    logo_zone.leds_count            = 1;
    logo_zone.matrix_map            = NULL;
    zones.push_back(logo_zone);

    led logo_led;
    logo_led.name                   = "Logo";
    leds.push_back(logo_led);

    SetupColors();
}

void RGBController_CreativeSoundBlasterXG6::ResizeZone(int /*zone*/, int /*new_size*/)
{
    /*---------------------------------------------------------*\
    | This device does not support resizing zones               |
    \*---------------------------------------------------------*/
}

void RGBController_CreativeSoundBlasterXG6::DeviceUpdateLEDs()
{
    unsigned char red = RGBGetRValue(colors[0]);
    unsigned char grn = RGBGetGValue(colors[0]);
    unsigned char blu = RGBGetBValue(colors[0]);

    controller->SetLedColor(red, grn, blu);
}

void RGBController_CreativeSoundBlasterXG6::UpdateZoneLEDs(int /*zone*/)
{
    DeviceUpdateLEDs();
}

void RGBController_CreativeSoundBlasterXG6::UpdateSingleLED(int /*led*/)
{
    DeviceUpdateLEDs();
}

void RGBController_CreativeSoundBlasterXG6::DeviceUpdateMode()
{
    DeviceUpdateLEDs();
}
