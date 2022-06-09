#include "Detector.h"
#include "ZalmanZSyncController.h"
#include "RGBController.h"
#include "RGBController_ZalmanZSync.h"
#include <vector>
#include <hidapi/hidapi.h>

#define ZALMAN_VID          0x1C57
#define ZALMAN_Z_SYNC_PID   0x7ED0

/******************************************************************************************\
*                                                                                          *
*   DetectZalmanZSyncControllers                                                           *
*                                                                                          *
*       Detect devices supported by the Zalman Z Sync driver                               *
*                                                                                          *
\******************************************************************************************/

void DetectZalmanZSyncControllers(hid_device_info* info, const std::string& name)
{
    hid_device* dev = hid_open_path(info->path);

    if(dev)
    {
        ZalmanZSyncController*     controller     = new ZalmanZSyncController(dev, info->path);
        RGBController_ZalmanZSync* rgb_controller = new RGBController_ZalmanZSync(controller);
        rgb_controller->name                      = name;

        ResourceManager::get()->RegisterRGBController(rgb_controller);
    }
}   /* DetectZalmanZSyncControllers() */

REGISTER_HID_DETECTOR("Zalman Z Sync", DetectZalmanZSyncControllers, ZALMAN_VID, ZALMAN_Z_SYNC_PID);
