#include "Detector.h"
#include "ThermaltakeRiingController.h"
#include "ThermaltakeRiingQuadController.h"
#include "RGBController.h"
#include "RGBController_ThermaltakeRiing.h"
#include "RGBController_ThermaltakeRiingQuad.h"
#include <vector>
#include <hidapi/hidapi.h>

#define THERMALTAKE_RIING_VID       0x264A
#define THERMALTAKE_RIING_PID_BEGIN 0x1FA5
#define THERMALTAKE_RIING_PID_END   0x1FB5

/******************************************************************************************\
*                                                                                          *
*   DetectThermaltakeRiingControllers                                                      *
*                                                                                          *
*       Tests the USB address to see if an AMD Wraith Prism controller exists there.       *
*                                                                                          *
\******************************************************************************************/

void DetectThermaltakeRiingControllers(hid_device_info* info, const std::string&)
{
    hid_device* dev = hid_open_path(info->path);
    if(dev)
    {
        ThermaltakeRiingController* controller = new ThermaltakeRiingController(dev, info->path);
        RGBController_ThermaltakeRiing* rgb_controller = new RGBController_ThermaltakeRiing(controller);
        // Constructor sets the name
        ResourceManager::get()->RegisterRGBController(rgb_controller);
    }
}   /* DetectThermaltakeRiingControllers() */

void DetectThermaltakeRiingQuadControllers(hid_device_info* info, const std::string&)
{
    hid_device* dev = hid_open_path(info->path);
    if(dev)
    {
        ThermaltakeRiingQuadController* controller = new ThermaltakeRiingQuadController(dev, info->path);
        RGBController_ThermaltakeRiingQuad* rgb_controller = new RGBController_ThermaltakeRiingQuad(controller);
        // Constructor sets the name
        ResourceManager::get()->RegisterRGBController(rgb_controller);
    }
}

REGISTER_HID_DETECTOR("Thermaltake Riing (PID 0x1FA5)", DetectThermaltakeRiingControllers, THERMALTAKE_RIING_VID, 0x1FA5);
REGISTER_HID_DETECTOR("Thermaltake Riing (PID 0x1FA6)", DetectThermaltakeRiingControllers, THERMALTAKE_RIING_VID, 0x1FA6);
REGISTER_HID_DETECTOR("Thermaltake Riing (PID 0x1FA7)", DetectThermaltakeRiingControllers, THERMALTAKE_RIING_VID, 0x1FA7);
REGISTER_HID_DETECTOR("Thermaltake Riing (PID 0x1FA8)", DetectThermaltakeRiingControllers, THERMALTAKE_RIING_VID, 0x1FA8);
REGISTER_HID_DETECTOR("Thermaltake Riing (PID 0x1FA9)", DetectThermaltakeRiingControllers, THERMALTAKE_RIING_VID, 0x1FA9);
REGISTER_HID_DETECTOR("Thermaltake Riing (PID 0x1FAA)", DetectThermaltakeRiingControllers, THERMALTAKE_RIING_VID, 0x1FAA);
REGISTER_HID_DETECTOR("Thermaltake Riing (PID 0x1FAB)", DetectThermaltakeRiingControllers, THERMALTAKE_RIING_VID, 0x1FAB);
REGISTER_HID_DETECTOR("Thermaltake Riing (PID 0x1FAC)", DetectThermaltakeRiingControllers, THERMALTAKE_RIING_VID, 0x1FAC);
REGISTER_HID_DETECTOR("Thermaltake Riing (PID 0x1FAD)", DetectThermaltakeRiingControllers, THERMALTAKE_RIING_VID, 0x1FAD);
REGISTER_HID_DETECTOR("Thermaltake Riing (PID 0x1FAE)", DetectThermaltakeRiingControllers, THERMALTAKE_RIING_VID, 0x1FAE);
REGISTER_HID_DETECTOR("Thermaltake Riing (PID 0x1FAF)", DetectThermaltakeRiingControllers, THERMALTAKE_RIING_VID, 0x1FAF);
REGISTER_HID_DETECTOR("Thermaltake Riing (PID 0x1FB0)", DetectThermaltakeRiingControllers, THERMALTAKE_RIING_VID, 0x1FB0);
REGISTER_HID_DETECTOR("Thermaltake Riing (PID 0x1FB1)", DetectThermaltakeRiingControllers, THERMALTAKE_RIING_VID, 0x1FB1);
REGISTER_HID_DETECTOR("Thermaltake Riing (PID 0x1FB2)", DetectThermaltakeRiingControllers, THERMALTAKE_RIING_VID, 0x1FB2);
REGISTER_HID_DETECTOR("Thermaltake Riing (PID 0x1FB3)", DetectThermaltakeRiingControllers, THERMALTAKE_RIING_VID, 0x1FB3);
REGISTER_HID_DETECTOR("Thermaltake Riing (PID 0x1FB4)", DetectThermaltakeRiingControllers, THERMALTAKE_RIING_VID, 0x1FB4);
REGISTER_HID_DETECTOR("Thermaltake Riing (PID 0x1FB5)", DetectThermaltakeRiingControllers, THERMALTAKE_RIING_VID, 0x1FB5);

REGISTER_HID_DETECTOR("Thermaltake Riing Quad (PID 0x2260)", DetectThermaltakeRiingQuadControllers, THERMALTAKE_RIING_VID, 0x2260);
REGISTER_HID_DETECTOR("Thermaltake Riing Quad (PID 0x2261)", DetectThermaltakeRiingQuadControllers, THERMALTAKE_RIING_VID, 0x2261);
REGISTER_HID_DETECTOR("Thermaltake Riing Quad (PID 0x2262)", DetectThermaltakeRiingQuadControllers, THERMALTAKE_RIING_VID, 0x2262);
REGISTER_HID_DETECTOR("Thermaltake Riing Quad (PID 0x2263)", DetectThermaltakeRiingQuadControllers, THERMALTAKE_RIING_VID, 0x2263);
REGISTER_HID_DETECTOR("Thermaltake Riing Quad (PID 0x2264)", DetectThermaltakeRiingQuadControllers, THERMALTAKE_RIING_VID, 0x2264);
REGISTER_HID_DETECTOR("Thermaltake Riing Quad (PID 0x2265)", DetectThermaltakeRiingQuadControllers, THERMALTAKE_RIING_VID, 0x2265);
REGISTER_HID_DETECTOR("Thermaltake Riing Quad (PID 0x2266)", DetectThermaltakeRiingQuadControllers, THERMALTAKE_RIING_VID, 0x2266);
REGISTER_HID_DETECTOR("Thermaltake Riing Quad (PID 0x2267)", DetectThermaltakeRiingQuadControllers, THERMALTAKE_RIING_VID, 0x2267);
REGISTER_HID_DETECTOR("Thermaltake Riing Quad (PID 0x2268)", DetectThermaltakeRiingQuadControllers, THERMALTAKE_RIING_VID, 0x2268);
REGISTER_HID_DETECTOR("Thermaltake Riing Quad (PID 0x2269)", DetectThermaltakeRiingQuadControllers, THERMALTAKE_RIING_VID, 0x2269);
REGISTER_HID_DETECTOR("Thermaltake Riing Quad (PID 0x226A)", DetectThermaltakeRiingQuadControllers, THERMALTAKE_RIING_VID, 0x226A);
REGISTER_HID_DETECTOR("Thermaltake Riing Quad (PID 0x226B)", DetectThermaltakeRiingQuadControllers, THERMALTAKE_RIING_VID, 0x226B);
REGISTER_HID_DETECTOR("Thermaltake Riing Quad (PID 0x226C)", DetectThermaltakeRiingQuadControllers, THERMALTAKE_RIING_VID, 0x226C);
REGISTER_HID_DETECTOR("Thermaltake Riing Quad (PID 0x226D)", DetectThermaltakeRiingQuadControllers, THERMALTAKE_RIING_VID, 0x226D);
REGISTER_HID_DETECTOR("Thermaltake Riing Quad (PID 0x226E)", DetectThermaltakeRiingQuadControllers, THERMALTAKE_RIING_VID, 0x226E);
REGISTER_HID_DETECTOR("Thermaltake Riing Quad (PID 0x226F)", DetectThermaltakeRiingQuadControllers, THERMALTAKE_RIING_VID, 0x226F);
REGISTER_HID_DETECTOR("Thermaltake Riing Quad (PID 0x2270)", DetectThermaltakeRiingQuadControllers, THERMALTAKE_RIING_VID, 0x2270);
