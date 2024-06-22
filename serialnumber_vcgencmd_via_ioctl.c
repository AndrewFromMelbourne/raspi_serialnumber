//-------------------------------------------------------------------------
//
// The MIT License (MIT)
//
// Copyright (c) 2024 Andrew Duncan
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//-------------------------------------------------------------------------

#include <fcntl.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/ioctl.h>

//-------------------------------------------------------------------------

#define RESPONSE_LENGTH 1024
#define PROPERTY_SIZE ((RESPONSE_LENGTH / 4) + 7)

//-------------------------------------------------------------------------

int main(void)
{
    int fd = open("/dev/vcio", 0);
    if (fd == -1)
    {
        perror("open /dev/vcio");
        exit(EXIT_FAILURE);
    }

    uint32_t property[PROPERTY_SIZE] =
    {
        0x00000000,
        0x00000000,
        0x00030080,
        RESPONSE_LENGTH,
        0x00000000,
        0x00000000,
    };

    const char *command = "otp_dump";
    memcpy(property + 6, command, strlen(command) + 1);
    property[0] = PROPERTY_SIZE * sizeof(property[0]);

    if (ioctl(fd, _IOWR(100, 0, char *), property) == -1)
    {
        perror("ioctl");
        exit(EXIT_FAILURE);
    }

    close(fd);

    uint32_t serial = 0;

    char *response = (char *)(property + 6);
    char *saveptr = NULL;
    char *token = strtok_r(response, "\n", &saveptr);

    while ((serial == 0) && (token != NULL))
    {
        int index;
        char value[100];

        if (sscanf(token, "%d:%s", &index, value) == 2)
        {
            if (index == 28)
            {
                serial = strtoul(value, 0, 16);
            }
            else if ((serial == 0) && (index == 31))
            {
                serial = strtoul(value, 0, 16);
            }
        }

        token = strtok_r(NULL, "\n", &saveptr);
    }

    printf("serial: %016"PRIx32"\n", serial);

    return 0;
}
