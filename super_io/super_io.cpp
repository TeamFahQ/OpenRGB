/*-----------------------------------------*\
|  super_io.cpp                             |
|                                           |
|  Functions for interfacing with Super-IO  |
|                                           |
|  Adam Honse (CalcProgrammer1) 2/11/2020   |
\*-----------------------------------------*/
#include "super_io.h"

#ifdef WIN32
#include <Windows.h>
#include "OlsApi.h"

#else
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int dev_port_fd;
#endif

/******************************************************************************************\
*                                                                                          *
*   superio_enter                                                                          *
*                                                                                          *
*   Put the Super IO chip into Extended Function Mode                                      *
*                                                                                          *
\******************************************************************************************/

void superio_enter(int ioreg)
{
#ifdef WIN32
    WriteIoPortByte(ioreg, 0x87);
    WriteIoPortByte(ioreg, 0x87);
#else
    unsigned char temp = 0x87;
    dev_port_fd = open("/dev/port", O_RDWR, "rw");
    
    if (dev_port_fd >= 0)
    {
        lseek(dev_port_fd, ioreg, SEEK_SET);
        if(write(dev_port_fd, &temp, 1) == -1)
        {
            return;
        }

        lseek(dev_port_fd, ioreg, SEEK_SET);
        if(write(dev_port_fd, &temp, 1) == -1)
        {
            return;
        }
        
        close(dev_port_fd);
    } 
#endif
}


/******************************************************************************************\
*                                                                                          *
*   superio_outb                                                                           *
*                                                                                          *
*   Write a byte to the Super IO configuration register                                    *
*                                                                                          *
\******************************************************************************************/

void superio_outb(int ioreg, int reg, int val)
{
#ifdef WIN32
    WriteIoPortByte(ioreg, reg);
    WriteIoPortByte(ioreg + 1, val);
#else
    dev_port_fd = open("/dev/port", O_RDWR, "rw");
    
    if (dev_port_fd >= 0)
    {
        lseek(dev_port_fd, ioreg, SEEK_SET);
        if(write(dev_port_fd, &reg, 1) == -1)
        {
            return;
        }

        if(write(dev_port_fd, &val, 1) == -1)
        {
            return;
        }

        close(dev_port_fd);
    }
#endif
}


/******************************************************************************************\
*                                                                                          *
*   superio_inb                                                                            *
*                                                                                          *
*   Read a byte to the Super IO configuration register                                     *
*                                                                                          *
\******************************************************************************************/

int superio_inb(int ioreg, int reg)
{
#ifdef WIN32
    WriteIoPortByte(ioreg, reg);
    return ReadIoPortByte(ioreg + 1);
#else
    unsigned char temp = 0;
    dev_port_fd = open("/dev/port", O_RDWR, "rw");

    if (dev_port_fd >= 0)  
    {
        lseek(dev_port_fd, ioreg, SEEK_SET);
        if(write(dev_port_fd, &reg, 1) == -1)
        {
            return -1;
        }

        if(read(dev_port_fd, &temp, 1) == -1)
        {
            return -1;
        }

        close(dev_port_fd);
        
        return((int)temp);
    }
    else
    {
        return -1;
    }
#endif
}
