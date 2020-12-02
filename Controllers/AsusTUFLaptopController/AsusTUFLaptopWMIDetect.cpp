#ifdef _WIN32

#include "RGBController_AsusTUFLaptopWMI.h"

#include "acpiwmi.h"
#include "Detector.h"
#include "wmi.h"
#include <string>

static void DetectAsusTUFLaptopWMIControllers(std::vector<RGBController*>&)
{
    // Try to retrieve ProductID / Device name from WMI; Possibly can be rewritten to use wmi.cpp
    // IF you encounter false detection ( e.g. if your laptop keyboard backlight uses USB interface
    // instead of ACPI WMI) please add a WHITELIST by checking the
    // `name` variable for model substrings like "FX505DU"
    // For now, checking for "TUF Gaming" should suffice

    Wmi wmi;
    wmi.init();

    std::vector<QueryObj> systemProduct;
    if (wmi.query("SELECT * FROM Win32_ComputerSystemProduct", systemProduct))
    {
        return;
    }

    // There should only be one, a cycle is a precaution
    if(systemProduct.size() != 1)
    {
        return;
    }
    std::string& name = systemProduct[0]["Name"];
    if(name.find("TUF Gaming") == name.npos)
    {
        return;
    }

    if(AsWMI_Open())
    {
        RGBController* new_controller = new RGBController_AsusTUFLaptopWMI();
        ResourceManager::get()->RegisterRGBController(new_controller);
        // Success! No more if's
    }
}   /* DetectFaustusControllers() */

REGISTER_DETECTOR("TUF Laptop WMI", DetectAsusTUFLaptopWMIControllers);

#endif
