#include "word_count.h"

#include <ctype.h>
#include <stddef.h>
#include <string.h>

const char delim = ' ';

static int update_count(word_count_word_t *words, size_t words_count, const char *word)
{
    size_t word_length = strlen(word);
    if (word_length > MAX_WORD_LENGTH)
    {
        return EXCESSIVE_LENGTH_WORD;
    }

    for (size_t i = 0; i < words_count; i++)
    {
        if (strncmp(words[i].text, word, MAX_WORD_LENGTH) == 0)
        {
            words[i].count++;

            return words_count;
        }
    }

    // new word
    if (words_count >= MAX_WORDS)
    {
        return EXCESSIVE_NUMBER_OF_WORDS;
    }

    strncpy(words[words_count].text, word, word_length);
    words[words_count].count = 1;

    words_count++;

    return words_count;
}

int count_words(const char *sentence, word_count_word_t *words)
{
    if (NULL == sentence || NULL == words)
        return INVAILD_PARAMETER;

    size_t length = strlen(sentence);
    if (0 == length)
    {
        return EXCESSIVE_LENGTH_WORD;
    }

    memset(words, 0, MAX_WORDS * sizeof(word_count_word_t));

    char sentence_copy[length + 1];
    sentence_copy[length] = '\0';

    // 预处理sentence
    for (size_t i = 0; i < length; i++)
    {
        if (isalpha(sentence[i]))
        {
            sentence_copy[i] = tolower(sentence[i]);
        }
        else if (isdigit(sentence[i]))
        {
            sentence_copy[i] = sentence[i];
        }
        else if (sentence[i] == '\'')
        {
            if (i == 0 || i == length - 1 || sentence[i - 1] == delim || sentence[i + 1] == delim)
            {
                sentence_copy[i] = delim;
            }
            else
            {
                sentence_copy[i] = sentence[i];
            }
        }
        else
        {
            sentence_copy[i] = delim;
        }
    }

    int words_count = 0;
    const char *word = strtok(sentence_copy, &delim);
    while (word != NULL)
    {
        if ((words_count = update_count(words, words_count, word)) < 0)
        {
            return words_count;
        }

        word = strtok(NULL, &delim);
    }

    return words_count;
}
