#include "rail_fence_cipher.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *encode(char *text, size_t rails)
{
    size_t length = strlen(text);
    if (0 == length || NULL == text || 0 == rails)
    {
        return NULL;
    }

    char cipher_table[rails][length];
    memset(cipher_table, 0, sizeof(cipher_table));

    int row_step = 1;
    for (size_t row = 0, col = 0; col < length; col++)
    {
        cipher_table[row][col] = text[col];
        row += row_step;
        if (row == rails - 1 || row == 0)
        {
            row_step *= -1;
        }
    }

    char *cipher = (char *)calloc(1, length + 1);
    if (NULL == cipher)
    {
        return NULL;
    }

    for (size_t row = 0, count = 0; row < rails; row++)
    {
        for (size_t col = 0; col < length; col++)
        {
            if (cipher_table[row][col] != 0)
            {
                cipher[count++] = cipher_table[row][col];
            }
        }
    }

    return cipher;
}

char *decode(char *ciphertext, size_t rails)
{
    size_t length = strlen(ciphertext);
    if (0 == length || NULL == ciphertext || 0 == rails)
    {
        return NULL;
    }

    char cipher_table[rails][length];
    memset(cipher_table, 0, sizeof(cipher_table));

    int row_step = 1;
    for (size_t row = 0, col = 0; col < length; col++)
    {
        cipher_table[row][col] = 1;
        row += row_step;
        if (row == rails - 1 || row == 0)
        {
            row_step *= -1;
        }
    }

    size_t count = 0;
    for (size_t row = 0; row < rails; row++)
    {
        for (size_t col = 0; col < length; col++)
        {
            if (1 == cipher_table[row][col])
            {
                cipher_table[row][col] = ciphertext[count++];
            }
        }
    }

    char *text = (char *)calloc(1, length + 1);
    if (NULL == text)
    {
        return NULL;
    }

    row_step = 1;
    for (size_t row = 0, col = 0; col < length; col++)
    {
        text[col] = cipher_table[row][col];
        row += row_step;
        if (row == rails - 1 || row == 0)
        {
            row_step *= -1;
        }
    }

    return text;
}
