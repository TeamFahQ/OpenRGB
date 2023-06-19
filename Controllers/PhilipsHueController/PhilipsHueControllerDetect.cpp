#include "Bridge.h"
#include "HueDeviceTypes.h"

#ifdef _WIN32
#include "WinHttpHandler.h"
#else
#include "LinHttpHandler.h"
#endif

#include "Detector.h"
#include "LogManager.h"
#include "PhilipsHueController.h"
#include "PhilipsHueEntertainmentController.h"
#include "RGBController_PhilipsHue.h"
#include "RGBController_PhilipsHueEntertainment.h"
#include "SettingsManager.h"

/******************************************************************************************\
*                                                                                          *
*   DetectPhilipsHueControllers                                                            *
*                                                                                          *
*       Detect Philips Hue lighting devices with RGB control                               *
*                                                                                          *
\******************************************************************************************/

void DetectPhilipsHueControllers()
{
    json                    hue_settings;

    /*-------------------------------------------------*\
    | Create an HTTP handler                            |
    \*-------------------------------------------------*/
#ifdef _WIN32
    using SystemHttpHandler = hueplusplus::WinHttpHandler;
#else
    using SystemHttpHandler = hueplusplus::LinHttpHandler;
#endif

    /*-------------------------------------------------*\
    | Get Philips Hue settings from settings manager    |
    \*-------------------------------------------------*/
    hue_settings = ResourceManager::get()->GetSettingsManager()->GetSettings("PhilipsHueDevices");

    /*-------------------------------------------------*\
    | Create a finder and find bridges                  |
    \*-------------------------------------------------*/
    static hueplusplus::BridgeFinder finder(std::make_shared<SystemHttpHandler>());
    std::vector<hueplusplus::BridgeFinder::BridgeIdentification> bridges;// = finder.findBridges();

    /*-------------------------------------------------*\
    | If no bridges were detected, manually add bridge  |
    | IP and MAC (need to get these from file)          |
    \*-------------------------------------------------*/
    if(bridges.empty())
    {
        if(hue_settings.contains("bridges"))
        {
            hueplusplus::BridgeFinder::BridgeIdentification ident;

            if(hue_settings["bridges"][0].contains("ip"))
            {
                ident.ip = hue_settings["bridges"][0]["ip"];
            }

            if(hue_settings["bridges"][0].contains("mac"))
            {
                ident.mac = hue_settings["bridges"][0]["mac"];
            }

            bridges.push_back(ident);
        }
    }

    /*-------------------------------------------------*\
    | If no bridges were found, return, otherwise       |
    | connect to the first bridge                       |
    \*-------------------------------------------------*/
    if(bridges.empty())
    {
        return;
    }
    else
    {
        /*-------------------------------------------------*\
        | Check if a saved username exists                  |
        \*-------------------------------------------------*/
        if(hue_settings.contains("bridges"))
        {
            /*-------------------------------------------------*\
            | Add the username if it exists                     |
            \*-------------------------------------------------*/
            if(hue_settings["bridges"][0].contains("username"))
            {
                finder.addUsername(bridges[0].mac, hue_settings["bridges"][0]["username"]);
            }

            /*-------------------------------------------------*\
            | Add the client key if it exists                   |
            \*-------------------------------------------------*/
            if(hue_settings["bridges"][0].contains("clientkey"))
            {
                finder.addClientKey(bridges[0].mac, hue_settings["bridges"][0]["clientkey"]);
            }
        }

        /*-------------------------------------------------*\
        | If username was added, this should connect right  |
        | away.  If not, the user will have to push the     |
        | connect button on the bridge.                     |
        \*-------------------------------------------------*/
        try
        {
            static hueplusplus::Bridge bridge = finder.getBridge(bridges[0]);

            bridge.refresh();

            /*-------------------------------------------------*\
            | Check to see if we need to save the settings      |
            | Settings need to be saved if either username or   |
            | client key either do not exist or have changed    |
            \*-------------------------------------------------*/
            bool save_settings = false;
            bool use_entertainment = false;
            bool auto_connect = false;

            if(hue_settings.contains("bridges"))
            {
                if(hue_settings["bridges"][0].contains("username"))
                {
                    if(hue_settings["bridges"][0]["username"] != bridge.getUsername())
                    {
                        save_settings = true;
                    }
                }
                else
                {
                    save_settings = true;
                }

                if(hue_settings["bridges"][0].contains("clientkey"))
                {
                    if(hue_settings["bridges"][0]["clientkey"] != bridge.getClientKey())
                    {
                        use_entertainment = true;
                        save_settings = true;
                    }
                }
                else
                {
                    save_settings = true;
                }
            }

            /*-------------------------------------------------*\
            | Save the settings if needed                       |
            \*-------------------------------------------------*/
            if(save_settings)
            {
                hue_settings["bridges"][0]["username"]       = bridge.getUsername();
                hue_settings["bridges"][0]["clientkey"]      = bridge.getClientKey();
                hue_settings["bridges"][0]["entertainment"]  = use_entertainment;
                hue_settings["bridges"][0]["autoconnect"]    = auto_connect;

                ResourceManager::get()->GetSettingsManager()->SetSettings("PhilipsHueDevices", hue_settings);

                ResourceManager::get()->GetSettingsManager()->SaveSettings();
            }

            /*-------------------------------------------------*\
            | Get entertainment mode settings                    |
            \*-------------------------------------------------*/
            if(hue_settings["bridges"][0].contains("entertainment"))
            {
                use_entertainment = hue_settings["bridges"][0]["entertainment"];
            }

            if(hue_settings["bridges"][0].contains("autoconnect"))
            {
                auto_connect = hue_settings["bridges"][0]["autoconnect"];
            }

            /*-------------------------------------------------*\
            | Get all groups from the bridge                    |
            \*-------------------------------------------------*/
            if(use_entertainment)
            {
                std::vector<hueplusplus::Group> groups = bridge.groups().getAll();

                if(groups.size() > 0)
                {
                    /*-------------------------------------------------*\
                    | Loop through all available groups and check to    |
                    | see if any are Entertainment groups               |
                    \*-------------------------------------------------*/
                    for(unsigned int group_idx = 0; group_idx < groups.size(); group_idx++)
                    {
                        if(groups[group_idx].getType() == "Entertainment")
                        {
                            PhilipsHueEntertainmentController*     controller     = new PhilipsHueEntertainmentController(bridge, groups[group_idx]);
                            RGBController_PhilipsHueEntertainment* rgb_controller = new RGBController_PhilipsHueEntertainment(controller);

                            ResourceManager::get()->RegisterRGBController(rgb_controller);
                        }
                    }

                    /*-------------------------------------------------*\
                    | Loop through RGB Controllers to find the first    |
                    | Entertainment group and Set it to "Connect",      |
                    | as only one Stream can be open at a time.         |
                    \*-------------------------------------------------*/
                    if(auto_connect)
                    {
                        for(unsigned int controller_idx = 0; controller_idx < ResourceManager::get()->GetRGBControllers().size(); controller_idx++)
                        {
                            if(ResourceManager::get()->GetRGBControllers()[controller_idx]->description == "Philips Hue Entertainment Mode Device")
                            {
                                ResourceManager::get()->GetRGBControllers()[controller_idx]->SetMode(0);
                                break;
                            }
                        }
                    }
                }
            }

            /*-------------------------------------------------*\
            | Get all lights from the bridge                    |
            \*-------------------------------------------------*/
            else
            {
                std::vector<hueplusplus::Light> lights = bridge.lights().getAll();

                if(lights.size() > 0)
                {
                    /*-------------------------------------------------*\
                    | Loop through all available lights and add those   |
                    | that have color (RGB) control capability          |
                    \*-------------------------------------------------*/
                    for(unsigned int light_idx = 0; light_idx < lights.size(); light_idx++)
                    {
                        if(lights[light_idx].hasColorControl())
                        {
                            PhilipsHueController*     controller     = new PhilipsHueController(lights[light_idx], bridge.getBridgeIP());
                            RGBController_PhilipsHue* rgb_controller = new RGBController_PhilipsHue(controller);

                            ResourceManager::get()->RegisterRGBController(rgb_controller);
                        }
                    }
                }
            }
        }
        catch(const std::exception &e)
        {
            LOG_INFO("Exception occurred in Philips Hue detection: %s", e.what());
        }
    }
}   /* DetectPhilipsHueControllers() */

REGISTER_DETECTOR("Philips Hue", DetectPhilipsHueControllers);
