/*-----------------------------------------*\
|  RGBController_AsusAuraMouse.h            |
|                                           |
|  Generic RGB Interface for Asus Aura      |
|  USB controller driver                    |
|                                           |
|  Adam Honse (CalcProgrammer1) 10/25/2020  |
\*-----------------------------------------*/

#pragma once
#include "RGBController.h"
#include "AsusAuraMouseController.h"

class RGBController_AuraMouse : public RGBController
{
public:
    RGBController_AuraMouse(AuraMouseController* aura_ptr);
    ~RGBController_AuraMouse();

    void        SetupZones();

    void        ResizeZone(int zone, int new_size);

    void        DeviceUpdateLEDs();
    void        UpdateZoneLEDs(int zone);
    void        UpdateSingleLED(int led);

    void        SetCustomMode();
    void        DeviceUpdateMode();

private:
    AuraMouseController*  aura;
};
