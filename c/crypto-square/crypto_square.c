#include "crypto_square.h"

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char *ciphertext(const char *input)
{
    assert(input != NULL);

    size_t input_len = strlen(input);

    char normalized[input_len + 1];
    size_t index = 0;

    for (size_t i = 0; i < input_len; i++)
    {
        if (isalpha(input[i]))
        {
            normalized[index++] = tolower(input[i]);
        }
        else if (isdigit(input[i]))
        {
            normalized[index++] = input[i];
        }
    }

    size_t cols = ceil(sqrt((float)index));
    size_t rows = cols * (cols - 1) > index ? cols - 1 : cols;

    char rectangle[rows][cols];
    memset(rectangle, ' ', rows * cols);

    for (size_t row = 0; row < rows; row++)
    {
        for (size_t col = 0; col < cols; col++)
        {
            if (row * cols + col < index)
            {
                rectangle[row][col] = normalized[row * cols + col];
            }
        }
    }

    char *cipher = (char *)calloc(1, ((rows + 1) * cols));
    index = 0;

    for (size_t col = 0; col < cols; col++)
    {
        for (size_t row = 0; row < rows; row++)
        {
            cipher[index++] = rectangle[row][col];
        }

        if (col == cols - 1)
        {
            cipher[index++] = '\0';
        }
        else
        {
            cipher[index++] = ' ';
        }
    }

    return cipher;
}
