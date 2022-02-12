#include "diamond.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char **make_diamond(const char letter)
{
    size_t width = 2 * (letter - 'A') + 1;
    size_t height = width;

    char **diamond = (char **)calloc(height, sizeof(char *));
    assert(diamond != NULL);

    for (size_t i = 0; i < height; i++)
    {
        diamond[i] = (char *)malloc(width + 1);
        assert(diamond[i] != 0);
        memset(diamond[i], ' ', width);
        diamond[i][width] = '\0';
    }

    size_t middle = height / 2;

    if (1 == height)
    {
        diamond[0][0] = 'A';
        return diamond;
    }
    else
    {
        diamond[0][middle] = 'A';
        diamond[height - 1][middle] = 'A';
        diamond[middle][0] = letter;
        diamond[middle][width - 1] = letter;
    }

    for (size_t i = 1; i < middle; i++)
    {
        char value = 'A' + i;
        diamond[i][middle + i] = value;
        diamond[i][middle - i] = value;

        diamond[height - 1 - i][middle + i] = value;
        diamond[height - 1 - i][middle - i] = value;
    }

    return diamond;
}