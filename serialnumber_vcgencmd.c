//-------------------------------------------------------------------------
//
// The MIT License (MIT)
//
// Copyright (c) 2015 Andrew Duncan
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

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include "bcm_host.h"
#pragma GCC diagnostic pop

//-------------------------------------------------------------------------

int main(void)
{
    bcm_host_init();

    char response[1024];
    uint32_t serial = 0;

    memset(response, 0, sizeof(response));

    if (vc_gencmd(response, sizeof(response), "otp_dump") == 0)
    {
        char *saveptr = NULL;
        char *token = strtok_r(response, "\n", &saveptr);

        while (token != NULL)
        {
            int index;
            char value[100];

            if (sscanf(token, "%d:%s", &index, value) == 2)
            {
                if (index == 28)
                {
                    serial = strtoul(value, 0, 16);
                }
            }

            token = strtok_r(NULL, "\n", &saveptr);
        }
    }

    printf("serial: %016"PRIx32"\n", serial);

    return 0;
}
