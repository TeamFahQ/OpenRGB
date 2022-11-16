/*-----------------------------------------*\
|  RGBController_MSIMysticLight185.h        |
|                                           |
|  Generic RGB Interface for OpenRGB        |
|  MSI Mystic Light (185-byte) USB Driver   |
|                                           |
|  T-bond 3/4/2020                          |
|  Adam Honse 3/6/2021                      |
\*-----------------------------------------*/

#pragma once
#include "RGBController.h"
#include "MSIMysticLight185Controller.h"
#include <vector>

class RGBController_MSIMysticLight185: public RGBController
{
public:
    RGBController_MSIMysticLight185(MSIMysticLight185Controller* controller_ptr);
    ~RGBController_MSIMysticLight185();

    void        SetupZones();
    void        ResizeZone(int zone, int new_size);

    void        DeviceUpdateLEDs();
    void        UpdateZoneLEDs(int zone);
    void        UpdateSingleLED(int led);

    void        DeviceUpdateMode();
    void        DeviceSaveMode();

private:
    void        SetupModes();
    void        UpdateLed
                    (
                    int zone,
                    int led
                    );
    void        SetupMode
                    (
                    const char      *name,
                    MSI_MODE        mode,
                    unsigned int    flags
                    );
    int         GetDeviceMode();
    void        GetDeviceConfig();

    MSIMysticLight185Controller*    controller;
    MSI_ZONE                        last_resizable_zone;
};
