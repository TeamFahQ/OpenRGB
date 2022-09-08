#include "Detector.h"
#include "AsusAuraCoreController.h"
#include "RGBController.h"
#include "RGBController_AsusAuraCore.h"
#include "RGBController_AsusAuraCoreLaptop.h"
#include <hidapi/hidapi.h>

#define AURA_CORE_VID                   0x0B05

#define AURA_STRIX_SCAR_15_PID          0x19B6

/******************************************************************************************\
*                                                                                          *
*   DetectAuraCoreControllers                                                              *
*                                                                                          *
*       Tests the USB address to see if an Asus ROG Aura Core controller exists there      *
*                                                                                          *
\******************************************************************************************/

void DetectAsusAuraCoreControllers(hid_device_info* info, const std::string& /*name*/)
{
    hid_device* dev = hid_open_path(info->path);

    if(dev)
    {
        AuraCoreController*     controller                  = new AuraCoreController(dev, info->path);
        RGBController_AuraCore* rgb_controller              = new RGBController_AuraCore(controller);
        // Constructor sets the name
        if(rgb_controller->type != DEVICE_TYPE_UNKNOWN)
        {
            ResourceManager::get()->RegisterRGBController(rgb_controller);
        }
        else
        {
            delete rgb_controller;
        }
    }
}

void DetectAsusAuraCoreLaptopControllers(hid_device_info* info, const std::string& /*name*/)
{
    hid_device* dev = hid_open_path(info->path);

    if(dev)
    {
        AsusAuraCoreLaptopController*     controller        = new AsusAuraCoreLaptopController(dev, info->path);
        RGBController_AsusAuraCoreLaptop* rgb_controller    = new RGBController_AsusAuraCoreLaptop(controller);
        // Constructor sets the name
        ResourceManager::get()->RegisterRGBController(rgb_controller);
    }
}


REGISTER_HID_DETECTOR   ("ASUS Aura Core",              DetectAsusAuraCoreControllers,          AURA_CORE_VID, 0x1854);
REGISTER_HID_DETECTOR   ("ASUS Aura Core",              DetectAsusAuraCoreControllers,          AURA_CORE_VID, 0x1866);
REGISTER_HID_DETECTOR   ("ASUS Aura Core",              DetectAsusAuraCoreControllers,          AURA_CORE_VID, 0x1869);
REGISTER_HID_DETECTOR_PU("ASUS ROG Strix SCAR 15",      DetectAsusAuraCoreLaptopControllers,    AURA_CORE_VID, AURA_STRIX_SCAR_15_PID,  0xFF31, 0x79);
