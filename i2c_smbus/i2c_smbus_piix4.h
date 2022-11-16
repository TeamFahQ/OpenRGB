/*-----------------------------------------*\
|  i2c_smbus_piix4.h                        |
|                                           |
|  Definitions and types for PIIX4 SMBUS    |
|  driver                                   |
|                                           |
|  Adam Honse (CalcProgrammer1) 8/8/2018    |
|  Portions based on Linux source code      |
|  GNU GPL v2                               |
\*-----------------------------------------*/

#include "i2c_smbus.h"
#include "windows.h"

#pragma once

// PIIX4 SMBus address offsets
#define SMBHSTSTS (0 + piix4_smba)
#define SMBHSLVSTS (1 + piix4_smba)
#define SMBHSTCNT (2 + piix4_smba)
#define SMBHSTCMD (3 + piix4_smba)
#define SMBHSTADD (4 + piix4_smba)
#define SMBHSTDAT0 (5 + piix4_smba)
#define SMBHSTDAT1 (6 + piix4_smba)
#define SMBBLKDAT (7 + piix4_smba)
#define SMBSLVCNT (8 + piix4_smba)
#define SMBSHDWCMD (9 + piix4_smba)
#define SMBSLVEVT (0xA + piix4_smba)
#define SMBSLVDAT (0xC + piix4_smba)

#define MAX_TIMEOUT     5000

// PIIX4 constants
#define PIIX4_QUICK             0x00
#define PIIX4_BYTE              0x04
#define PIIX4_BYTE_DATA         0x08
#define PIIX4_WORD_DATA         0x0C
#define PIIX4_BLOCK_DATA        0x14

#define GLOBAL_SMBUS_MUTEX_NAME "Global\\Access_SMBUS.HTP.Method"

class i2c_smbus_piix4 : public i2c_smbus_interface
{
public:
	u16 piix4_smba = 0x0B00;
    i2c_smbus_piix4();
    ~i2c_smbus_piix4();

private:
    int piix4_transaction();
    s32 piix4_access(u16 addr, char read_write, u8 command, int size, i2c_smbus_data *data);
    s32 i2c_smbus_xfer(u8 addr, char read_write, u8 command, int size, i2c_smbus_data* data);
    s32 i2c_xfer(u8 addr, char read_write, int* size, u8* data);
    HANDLE delay_timer;
    HANDLE global_smbus_access_handle = NULL;
};
