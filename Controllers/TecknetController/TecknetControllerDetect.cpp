/*-------------------------------------------------------------------*\
|  TecknetControllerDetect.cpp                                        |
|                                                                     |
|  Driver for Tecknet Devices                                         |
|                                                                     |
|  Chris M (Dr_No)          29th Jul 2020                             |
|                                                                     |
\*-------------------------------------------------------------------*/

#include "Detector.h"
#include "TecknetController.h"
#include "RGBController.h"
#include "RGBController_Tecknet.h"
#include <hidapi/hidapi.h>

#define TECKNET_VID             0x04D9

#define TECKNET_M0008_PID       0xFC05
#define TECKNET_M0008_U         0x01        //Usage 01
#define TECKNET_M0008_UPG       0xFFA0      //Vendor Defined Usage Page

/******************************************************************************************\
*                                                                                          *
*   DetectTecknetControllers                                                               *
*                                                                                          *
*       Tests the USB address to see if any Tecknet Controllers.                           *
*                                                                                          *
\******************************************************************************************/

void DetectTecknetControllers(hid_device_info* info, const std::string&)
{
    hid_device* dev = hid_open_path(info->path);
    if(dev)
    {
        TecknetController* controller = new TecknetController(dev, info->path);
        RGBController_Tecknet* rgb_controller = new RGBController_Tecknet(controller);
        // Constructor sets the name
        ResourceManager::get()->RegisterRGBController(rgb_controller);
    }
}   /* DetectTecknetControllers) */

#ifdef USE_HID_USAGE
REGISTER_HID_DETECTOR_PU("Tecknet M008", DetectTecknetControllers, TECKNET_VID, TECKNET_M0008_PID, TECKNET_M0008_UPG, TECKNET_M0008_U);
#else
REGISTER_HID_DETECTOR_I("Tecknet M008", DetectTecknetControllers, TECKNET_VID, TECKNET_M0008_PID, 0);
#endif
