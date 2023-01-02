#include "Detector.h"
#include "RGBController.h"
#include "hidapi/hidapi.h"
#include "GigabyteAorusMouseController.h"
#include "RGBController_GigabyteAorusMouse.h"

/*-----------------------------------------------------*\
| Vendor ID                                             |
\*-----------------------------------------------------*/
#define HOLTEK_VID                                 0x1044

/*-----------------------------------------------------*\
| Controller product ids                                |
\*-----------------------------------------------------*/
#define AORUS_M2_PID                               0x7A40

void DetectGigabyteAorusMouseControllers(hid_device_info* info, const std::string& name)
{
    hid_device* dev = hid_open_path(info->path);

    if(dev)
    {
        GigabyteAorusMouseController*     controller         = new GigabyteAorusMouseController(dev, *info);
        RGBController_GigabyteAorusMouse* rgb_controller     = new RGBController_GigabyteAorusMouse(controller);
        rgb_controller->name                     = name;

        ResourceManager::get()->RegisterRGBController(rgb_controller);
    }
}

REGISTER_HID_DETECTOR_IPU("Gigabyte Aorus M2", DetectGigabyteAorusMouseControllers, HOLTEK_VID, AORUS_M2_PID, 3, 0xFF01, 0x01);
