#include "two_fer.h"

#include <stdio.h>

#define BUFFER_SIZE (100)

void two_fer(char *buffer, const char *name)
{
    if (NULL == name)
    {
        name = "you";
    }

    snprintf(buffer, BUFFER_SIZE, "One for %s, one for me.", name);
}
