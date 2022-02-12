#include "etl.h"

#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define ALPHA_NUM (26)

int convert(const legacy_map *input, const size_t input_len, new_map **output)
{
    size_t count = 0;

    int map_table[ALPHA_NUM] = {0};

    for (size_t i = 0; i < input_len; i++)
    {
        const char *keys = input[i].keys;
        size_t len = strlen(keys);
        for (size_t j = 0; j < len; j++)
        {
            map_table[tolower(keys[j]) - 'a'] = input[i].value;
        }

        count += len;
    }

    *output = (new_map *)calloc(count, sizeof(new_map));
    count = 0;

    for (size_t i = 0; i < ALPHA_NUM; i++)
    {
        if (map_table[i] != 0)
        {
            new_map *map = *output;
            (map[count]).key = 'a' + i;
            (map[count]).value = map_table[i];

            count++;
        }
    }

    return count;
}
