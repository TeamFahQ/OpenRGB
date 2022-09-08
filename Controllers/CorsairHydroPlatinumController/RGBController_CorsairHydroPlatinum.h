/*-------------------------------------------------------------------*\
|  RGBController_CorsairHydroPlatinum.h                               |
|                                                                     |
|  Driver for Corsair Hydro Platinum AIO Coolers                      |
|                                                                     |
|  Kasper         28th March 2021                                     |
|                                                                     |
\*-------------------------------------------------------------------*/

#pragma once
#include "RGBController.h"
#include "CorsairHydroPlatinumController.h"

class RGBController_CorsairHydroPlatinum : public RGBController
{
public:
    RGBController_CorsairHydroPlatinum(CorsairHydroPlatinumController* controller_ptr);

    void        SetupZones();

    void        ResizeZone(int zone, int new_size);

    void        DeviceUpdateLEDs();
    void        UpdateZoneLEDs(int zone);
    void        UpdateSingleLED(int led);

    void        DeviceUpdateMode();

private:
    CorsairHydroPlatinumController* controller;

    void        Init_Controller();
};
