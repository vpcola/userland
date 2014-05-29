#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>

/* This function is borrowed from i2ctools package */

int main(int argc, char * argv[])
{
    int file, counter;
    const char * i2cbus="/dev/i2c-1";
    // Data write contains reg address byte[0] plus
    // actual data in byte [1]
    char buf[2];


    // Open the i2c
    file = open(i2cbus, O_WRONLY);
    if (file < 0)
    {
        printf("Failed to open file: %s\n", i2cbus);
        exit(1);
    }

    // Set the device address via IOCTL
    if (ioctl(file, I2C_SLAVE, 0x21) < 0)
    {
        printf("Failes setting device address\n");
        exit(1);
    }

    // We set the direction registers first
    buf[0] = 0x00; // Port b
    buf[1] = 0x00; // All bits set as output
    if (write(file, buf, 2) != 2)
    {
        printf("Failed to write to i2c device\n");
        exit(1);
    }

    for(counter = 0; counter < 100; counter++)
    {
        // We write to register 0x14 for the leds
        buf[0] = 0x14;
        buf[1] = (char) counter;

        if (write(file, buf, 2) != 2) 
        {
            printf("Failed to write data to device\n");
            exit(1);
        }

        sleep(1);
    }

    close(file);

}

