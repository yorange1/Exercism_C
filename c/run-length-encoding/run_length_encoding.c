#include "run_length_encoding.h"

#define _GNU_SOURCE
#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COUNT_STR_LEN (20)
#define DECODE_TEXT_LEN (1024)

static void encode_element(char *data, char element, size_t count)
{
    char *temp = NULL;

    if (1 == count)
    {
        asprintf(&temp, "%c", element);
    }
    else
    {
        asprintf(&temp, "%ld%c", count, element);
    }

    strcat(data, temp);

    free(temp);
}

char *encode(const char *text)
{
    assert(text != NULL);

    size_t len = strlen(text);
    char *data = (char *)calloc(1, len + 1);
    assert(data != NULL);

    if (len == 1)
    {
        data[0] = text[0];
    }
    else if (len > 1)
    {
        char prev = text[0];
        char curr;
        size_t count = 1;
        for (size_t i = 1; i < len; i++)
        {
            curr = text[i];
            if (curr != prev)
            {
                encode_element(data, prev, count);
                count = 1;
            }
            else
            {
                count++;
            }

            prev = curr;
        }

        // encode the last character
        encode_element(data, prev, count);
    }

    return data;
}

static void decode_element(char *text, char element, size_t count)
{
    char temp[2] = {0};
    temp[0] = element;

    for (size_t i = 0; i < count; i++)
    {
        strcat(text, temp);
    }
}

char *decode(const char *data)
{
    assert(data != NULL);

    size_t len = strlen(data);
    char *text = (char *)calloc(1, DECODE_TEXT_LEN);
    assert(text != NULL);

    if (len == 1)
    {
        text[0] = data[0];
    }
    else if (len > 1)
    {
        for (size_t i = 0; i < len; i++)
        {
            if (isdigit(data[i]))
            {
                char count_str[COUNT_STR_LEN];
                memset(count_str, 0, COUNT_STR_LEN);
                size_t index = 0;
                do
                {
                    count_str[index] = data[i];
                    index++;
                    i++;
                } while (isdigit(data[i]));

                char element = data[i];
                int count = atoi(count_str);
                decode_element(text, element, count);
            }
            else
            {
                decode_element(text, data[i], 1);
            }
        }
    }

    return text;
}
