#include "binary.h"

#include <stddef.h>
#include <string.h>

int convert(const char *input)
{
    size_t length = strlen(input);

    int result = 0;

    for (size_t i = 0; i < length; i++)
    {
        if (input[i] != '0' && input[i] != '1')
        {
            return INVALID;
        }

        result = (result << 1) + (input[i] == '1' ? 1 : 0);
    }

    return result;
}
