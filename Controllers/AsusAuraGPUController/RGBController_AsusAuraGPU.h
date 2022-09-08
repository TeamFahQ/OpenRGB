/*-----------------------------------------*\
|  RGBController_AsusAuraGPU.h              |
|                                           |
|  Generic RGB Interface for Asus Aura GPU  |
|                                           |
|  Jan Rettig (Klapstuhl) 14.02.2020        |
\*-----------------------------------------*/

#pragma once

#include "RGBController.h"
#include "AsusAuraGPUController.h"

class RGBController_AuraGPU : public RGBController
{
public:
    RGBController_AuraGPU(AuraGPUController* controller_ptr);
    ~RGBController_AuraGPU();

    void        SetupZones();

    void        ResizeZone(int zone, int new_size);

    void        DeviceUpdateLEDs();
    void        UpdateZoneLEDs(int zone);
    void        UpdateSingleLED(int led);

    void        DeviceUpdateMode();

private:
    AuraGPUController* controller;

    int        GetDeviceMode();
};
