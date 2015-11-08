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

#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//-----------------------------------------------------------------------
//
// Remove leading and trailing whitespace from a string.

static char *
trimWhiteSpace(
    char *string)
{
    if (string == NULL)
    {
        return NULL;
    }

    while (isspace(*string))
    {
        string++;
    }

    if (*string == '\0')
    {
        return string;
    }

    char *end = string;

    while (*end)
    {
        ++end;
    }
    --end;

    while ((end > string) && isspace(*end))
    {
        end--;
    }

    *(end + 1) = 0;
    return string;
}

//-----------------------------------------------------------------------

int main(void)
{
    uint32_t serial = 0;

    FILE *fp = fopen("/proc/cpuinfo", "r");

    if (fp == NULL)
    {
        perror("/proc/cpuinfo");
        exit(EXIT_FAILURE);
    }

    char entry[80];

    while (fgets(entry, sizeof(entry), fp) != NULL)
    {
        char* saveptr = NULL;

        char *key = trimWhiteSpace(strtok_r(entry, ":", &saveptr));
        char *value = trimWhiteSpace(strtok_r(NULL, ":", &saveptr));

        if (strcasecmp("Serial", key) == 0)
        {
            serial = strtol(value, NULL, 16);
        }
    }

    fclose(fp);

	printf("serial: %016"PRIx32"\n", serial);

    return 0;
}

