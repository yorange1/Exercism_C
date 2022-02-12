#include "atbash_cipher.h"

#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// zyxwvutsrqponmlkjihgfedcba
static const char atbash_alphabet[26] = {'z', 'y', 'x', 'w', 'v', 'u', 't', 's', 'r', 'q',
                                         'p', 'o', 'n', 'm', 'l', 'k', 'j', 'i', 'h', 'g',
                                         'f', 'e', 'd', 'c', 'b', 'a'};

static const int MAX_LEN = 1024;

char *atbash_encode(const char *input)
{
    assert(input != NULL);

    size_t len = strlen(input);

    char *cipher = (char *)calloc(1, MAX_LEN);
    assert(cipher != NULL);

    size_t cipher_index = 0;

    for (size_t i = 0; i < len; i++)
    {
        if (isalpha(input[i]))
        {
            cipher[cipher_index] = atbash_alphabet[tolower(input[i]) - 'a'];
            cipher_index++;
        }
        else if (isdigit(input[i]))
        {
            cipher[cipher_index] = input[i];
            cipher_index++;
        }

        if ((cipher_index + 1) % 6 == 0 && cipher_index != 0)
        {
            cipher[cipher_index] = ' ';
            cipher_index++;
        }
    }

    if (cipher[cipher_index - 1] == ' ')
    {
        cipher[cipher_index - 1] = '\0';
    }

    return cipher;
}

char *atbash_decode(const char *input)
{
    assert(input != NULL);

    size_t len = strlen(input);

    char *text = (char *)calloc(1, MAX_LEN);
    assert(text != NULL);

    size_t text_index = 0;
    for (size_t i = 0; i < len; i++)
    {
        if (isalpha(input[i]))
        {
            text[text_index] = atbash_alphabet[tolower(input[i]) - 'a'];
            text_index++;
        }
        else if (isdigit(input[i]))
        {
            text[text_index] = input[i];
            text_index++;
        }
    }

    return text;
}
