#include "Detector.h"
#include "MountainKeyboardController.h"
#include "RGBController.h"
#include "RGBController_MountainKeyboard.h"
#include <hidapi/hidapi.h>

/*----------------------------------------------------------------------------------------*\
|                                                                                          |
|   DetectMountainKeyboardControllers                                                      |
|                                                                                          |
|       Tests the USB address to see if a Mountain RGB Keyboard controller exists there.   |
|                                                                                          |
\*----------------------------------------------------------------------------------------*/

void DetectMountainKeyboardControllers(hid_device_info* info, const std::string& name)
{
    hid_device* dev = hid_open_path(info->path);

    if(dev)
    {
        MountainKeyboardController*     controller     = new MountainKeyboardController(dev, info->path);
        RGBController_MountainKeyboard* rgb_controller = new RGBController_MountainKeyboard(controller);
        rgb_controller->name = name;
        ResourceManager::get()->RegisterRGBController(rgb_controller);
    }
}   /* DetectMountainKeyboardControllers() */

REGISTER_HID_DETECTOR_IPU("Mountain Everest", DetectMountainKeyboardControllers, MOUNTAIN_VID, MOUNTAIN_EVEREST_PID, 3, 0xFF00, 0x01);

