#include "isogram.h"

#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

bool is_isogram(const char phrase[])
{
    if (NULL == phrase)
    {
        return false;
    }

    size_t len = strlen(phrase);
    if (len <= 1)
    {
        return true;
    }

    uint32_t flags = 0;

    for (size_t i = 0; i < len; i++)
    {
        if (isalpha(phrase[i]))
        {
            size_t index = islower(phrase[i]) ? phrase[i] - 'a' : phrase[i] - 'A';
            if ((flags & (1 << index)) != 0)
            {
                return false;
            }
            else
            {
                flags |= (1 << index);
            }
        }
    }

    return true;
}
