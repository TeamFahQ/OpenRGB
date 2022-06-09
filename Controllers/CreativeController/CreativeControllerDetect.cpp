#include "CreativeSoundBlasterXG6Controller.h"
#include "RGBController_CreativeSoundBlasterXG6.h"
#include "Detector.h"
#include <hidapi/hidapi.h>

/*-----------------------------------------------------*\
| Creative vendor ID                                    |
\*-----------------------------------------------------*/
#define CREATIVE_VID                            0x041E
/*-----------------------------------------------------*\
| SoundCards                                            |
\*-----------------------------------------------------*/
#define CREATIVE_SOUNDBLASTERX_G6_PID           0x3256

void DetectCreativeDevice(hid_device_info* info, const std::string& name)
{
    hid_device* dev = hid_open_path(info->path);
    
    if(dev)
    {
        CreativeSoundBlasterXG6Controller*     controller     = new CreativeSoundBlasterXG6Controller(dev, info->path);
        RGBController_CreativeSoundBlasterXG6* rgb_controller = new RGBController_CreativeSoundBlasterXG6(controller);
        rgb_controller->name = name;
        ResourceManager::get()->RegisterRGBController(rgb_controller);
    }
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------*\
| Sound Cards                                                                                                                                       |
\*-------------------------------------------------------------------------------------------------------------------------------------------------*/
REGISTER_HID_DETECTOR_I("Creative SoundBlasterX G6",               DetectCreativeDevice,         CREATIVE_VID,     CREATIVE_SOUNDBLASTERX_G6_PID, 4);
