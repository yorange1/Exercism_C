#include "pig_latin.h"

#define _GNU_SOURCE
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool is_vowel(char ch)
{
    return ('a' == ch || 'e' == ch || 'i' == ch || 'o' == ch || 'u' == ch);
}

static bool is_rule1(const char *phrase)
{
    return (is_vowel(phrase[0]) || ('x' == phrase[0] && 'r' == phrase[1]) || ('y' == phrase[0] && 't' == phrase[1]));
}

static char *add_ay(const char *phrase)
{
    char *res = NULL;

    int ret = asprintf(&res, "%say", phrase);
    assert(ret > 0);

    return res;
}

static void left_shift(char *phrase, size_t len)
{
    char to_end = phrase[0];

    memmove(phrase, &phrase[1], len - 1);
    phrase[len - 1] = to_end;
}

static char *translate_word(char *word)
{
    assert(NULL != word);

    if (is_rule1(word))
    {
        // begins with a vowel or "xr" or "yt"
        return add_ay(word);
    }

    size_t len = strlen(word);
    char *copy = (char *)calloc(1, len + 1);
    strncpy(copy, word, len);

    if (2 == len && 'y' == copy[1])
    {
        // "y" as the second letter in a two letter word
        left_shift(copy, len);
    }
    else
    {
        size_t count = 0;
        while (1)
        {
            if (is_vowel(copy[0]) || ('y' == copy[0] && count > 0))
            {
                break;
            }
            else if ('q' == copy[0] && 'u' == copy[1])
            {
                left_shift(copy, len);
                left_shift(copy, len);
                break;
            }
            else
            {
                // begins with a consonant
                left_shift(copy, len);
                count++;
            }
        }
    }

    char *res = add_ay(copy);
    free(copy);
    return res;
}

char *translate(const char *phrase)
{
    assert(NULL != phrase);

    size_t len = strlen(phrase);
    char *copy = (char *)calloc(1, len + 1);
    strncpy(copy, phrase, len);

    char delim = ' ';
    char *word = strtok(copy, &delim);
    size_t count = 0;

    char *res = NULL;

    while (NULL != word)
    {
        char *res_word = translate_word(word);

        if (0 == count)
        {
            res = res_word;
        }
        else
        {
            char *tmp = res;

            int ret = asprintf(&res, "%s %s", res, res_word);
            assert(ret > 0);

            free(tmp);
        }

        word = strtok(NULL, &delim);
        count++;
    }

    free(copy);

    return res;
}
