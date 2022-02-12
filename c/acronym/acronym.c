#include "acronym.h"

#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

const char *delim = " ";

char *abbreviate(const char *phrase)
{
    if (phrase == NULL)
        return NULL;

    size_t length = strlen(phrase);
    if (length == 0)
    {
        return NULL;
    }

    char copy[length + 1];
    for (size_t i = 0; i < length; i++)
    {
        if (phrase[i] == '-' || phrase[i] == '_')
        {
            copy[i] = ' ';
        }
        else
        {
            copy[i] = phrase[i];
        }
    }

    char temp[length + 1];
    size_t count = 0;

    char *sub = strtok(copy, delim);
    while (sub != NULL)
    {
        char first_char = *sub;
        if (isalpha(first_char))
        {
            temp[count++] = toupper(first_char);
        }

        sub = strtok(NULL, delim);
    }

    char *result = (char *)calloc(1, count + 1);
    if (NULL == result)
    {
        return NULL;
    }

    strncpy(result, temp, count);

    return result;
}