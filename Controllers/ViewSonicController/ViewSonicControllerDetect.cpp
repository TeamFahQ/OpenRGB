#include "Detector.h"
#include "VS_XG270QG_Controller.h"
#include "RGBController_XG270QG.h"
#include <hidapi/hidapi.h>

#include "LogManager.h"

#define VIEWSONIC_VID 0x0416
#define VS_XG270QG_PID 0x5020

void DetectViewSonic(hid_device_info* info, const std::string& name)
{
    hid_device* dev = hid_open_path(info->path);

    if(dev)
    {
        VS_XG270QG_Controller* controller     = new VS_XG270QG_Controller(dev, info->path);
        RGBController_XG270QG* rgb_controller = new RGBController_XG270QG(controller);
        rgb_controller->name                  = name;
        
        ResourceManager::get()->RegisterRGBController(rgb_controller);
    }
}

REGISTER_HID_DETECTOR("ViewSonic Monitor XG270QG", DetectViewSonic,        VIEWSONIC_VID, VS_XG270QG_PID);
