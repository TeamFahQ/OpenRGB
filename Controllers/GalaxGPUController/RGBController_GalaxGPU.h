/*-----------------------------------------*\
|  RGBController_GalaxGPU.h                 |
|                                           |
|  Driver for Galax / KFA2 RGB on GPUs      |
|                                           |
|  Niels Westphal (crashniels)  12.07.2020  |
\*-----------------------------------------*/

#pragma once

#include "RGBController.h"
#include "GalaxGPUController.h"

class RGBController_GalaxGPU : public RGBController
{
public:
    RGBController_GalaxGPU(GalaxGPUController* controller_ptr);
    ~RGBController_GalaxGPU();

    void        SetupZones();

    void        ResizeZone(int zone, int new_size);

    void        DeviceUpdateLEDs();
    void        UpdateZoneLEDs(int zone);
    void        UpdateSingleLED(int led);

    void        DeviceUpdateMode();

private:
    GalaxGPUController* controller;

    int        GetDeviceMode();
};
