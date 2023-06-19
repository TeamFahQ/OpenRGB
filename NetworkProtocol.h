/*-----------------------------------------*\
|  NetworkProtocol.h                        |
|                                           |
|  Protocol header for OpenRGB SDK          |
|                                           |
|  Adam Honse (CalcProgrammer1) 5/9/2020    |
\*-----------------------------------------*/

#pragma once

/*---------------------------------------------------------------------*\
| OpenRGB SDK protocol version                                          |
|                                                                       |
|   0:      Initial (unversioned) protocol                              |
|   1:      Add versioning, vendor string (Release 0.5)                 |
|   2:      Add profile controls (Release 0.6)                          |
|   3:      Add brightness field to modes (Release 0.7)                 |
|   4:      Add segments field to zones, network plugins (Release 0.9)  |
\*---------------------------------------------------------------------*/
#define OPENRGB_SDK_PROTOCOL_VERSION    4

/*-----------------------------------------------------*\
| Default Interface to bind to.                         |
\*-----------------------------------------------------*/
#define OPENRGB_SDK_HOST "0.0.0.0"

/*-----------------------------------------------------*\
| Default OpenRGB SDK port is 6742                      |
| This is "ORGB" on a phone keypad                      |
\*-----------------------------------------------------*/
#define OPENRGB_SDK_PORT 6742

typedef struct NetPacketHeader
{
    char                pkt_magic[4];               /* Magic value "ORGB" identifies beginning of packet    */
    unsigned int        pkt_dev_idx;                /* Device index                                         */
    unsigned int        pkt_id;                     /* Packet ID                                            */
    unsigned int        pkt_size;                   /* Packet size                                          */
} NetPacketHeader;

enum
{
    /*----------------------------------------------------------------------------------------------------------*\
    | Network requests                                                                                           |
    \*----------------------------------------------------------------------------------------------------------*/
    NET_PACKET_ID_REQUEST_CONTROLLER_COUNT      = 0,    /* Request RGBController device count from server       */
    NET_PACKET_ID_REQUEST_CONTROLLER_DATA       = 1,    /* Request RGBController data block                     */

    NET_PACKET_ID_REQUEST_PROTOCOL_VERSION      = 40,   /* Request OpenRGB SDK protocol version from server     */

    NET_PACKET_ID_SET_CLIENT_NAME               = 50,   /* Send client name string to server                    */

    NET_PACKET_ID_DEVICE_LIST_UPDATED           = 100,  /* Indicate to clients that device list has updated     */

    NET_PACKET_ID_REQUEST_PROFILE_LIST          = 150,  /* Request profile list                                 */
    NET_PACKET_ID_REQUEST_SAVE_PROFILE          = 151,  /* Save current configuration in a new profile          */
    NET_PACKET_ID_REQUEST_LOAD_PROFILE          = 152,  /* Load a given profile                                 */
    NET_PACKET_ID_REQUEST_DELETE_PROFILE        = 153,  /* Delete a given profile                               */

    NET_PACKET_ID_REQUEST_PLUGIN_LIST           = 200,  /* Request list of plugins                              */
    NET_PACKET_ID_PLUGIN_SPECIFIC               = 201,  /* Interact with a plugin                               */

    /*----------------------------------------------------------------------------------------------------------*\
    | RGBController class functions                                                                              |
    \*----------------------------------------------------------------------------------------------------------*/
    NET_PACKET_ID_RGBCONTROLLER_RESIZEZONE      = 1000, /* RGBController::ResizeZone()                          */

    NET_PACKET_ID_RGBCONTROLLER_UPDATELEDS      = 1050, /* RGBController::UpdateLEDs()                          */
    NET_PACKET_ID_RGBCONTROLLER_UPDATEZONELEDS  = 1051, /* RGBController::UpdateZoneLEDs()                      */
    NET_PACKET_ID_RGBCONTROLLER_UPDATESINGLELED = 1052, /* RGBController::UpdateSingleLED()                     */

    NET_PACKET_ID_RGBCONTROLLER_SETCUSTOMMODE   = 1100, /* RGBController::SetCustomMode()                       */
    NET_PACKET_ID_RGBCONTROLLER_UPDATEMODE      = 1101, /* RGBController::UpdateMode()                          */
    NET_PACKET_ID_RGBCONTROLLER_SAVEMODE        = 1102, /* RGBController::SaveMode()                            */
};
