/*-----------------------------------------*\
|  IonicoControllerDetect.cpp               |
|                                           |
|  Driver for the Ionico-II-17 lighting     |
|  controller                               |
|                                           |
|  Lucas Strafe 31/12/2022                  |
\*-----------------------------------------*/

#include "Detector.h"
#include "RGBController.h"
#include "hidapi/hidapi.h"
#include "IonicoController.h"
#include "RGBController_Ionico.h"

/*-----------------------------------------------------*\
|                     FRONT BAR                         |
\*-----------------------------------------------------*/
#define IONICO_FB_VID        0x048D
#define IONICO_FB_PID        0x6005

/*-----------------------------------------------------*\
|                     KEYBOARD                          |
\*-----------------------------------------------------*/
#define IONICO_KB_VID        0x048D
#define IONICO_KB_PID        0xCE00


void DetectIonicoControllers(hid_device_info* info, const std::string& name)
{
    hid_device* dev = hid_open_path(info->path);

    if(dev)
    {
        IonicoController*     controller         = new IonicoController(dev, *info, info->product_id);
        RGBController_Ionico* rgb_controller     = new RGBController_Ionico(controller);
        rgb_controller->name                     = name;

        if(info->product_id == IONICO_KB_PID)
        {
            rgb_controller->type = DEVICE_TYPE_KEYBOARD;
        }
        else if(info->product_id == IONICO_FB_PID)
        {
            rgb_controller->type = DEVICE_TYPE_LEDSTRIP;
        }
        ResourceManager::get()->RegisterRGBController(rgb_controller);
    }
}

REGISTER_HID_DETECTOR_PU("Ionico Light Bar", DetectIonicoControllers, IONICO_FB_VID, IONICO_FB_PID,  0xFF03, 0x01);
REGISTER_HID_DETECTOR_PU("Ionico Keyboard", DetectIonicoControllers, IONICO_KB_VID, IONICO_KB_PID,  0xFF12, 0x01);
