#include "wordy.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char get_operation(char *substr, const char *delim)
{
    // operations
    char operation = 0;
    if (NULL == substr)
    {
        operation = ' ';
    }
    else if (strcmp(substr, "plus") == 0)
    {
        operation = '+';
    }
    else if (strcmp(substr, "minus") == 0)
    {
        operation = '-';
    }
    else if (strcmp(substr, "multiplied") == 0)
    {
        substr = strtok(NULL, delim);
        if (strcmp(substr, "by") == 0)
        {
            operation = '*';
        }
    }
    else if (strcmp(substr, "divided") == 0)
    {
        substr = strtok(NULL, delim);
        if (strcmp(substr, "by") == 0)
        {
            operation = '/';
        }
    }

    return operation;
}

static int calculate(int number1, int number2, char operation)
{
    int answer = 0;

    switch (operation)
    {
    case '+':
        answer = number1 + number2;
        break;
    case '-':
        answer = number1 - number2;
        break;
    case '*':
        answer = number1 * number2;
        break;
    case '/':
        answer = number1 / number2;
        break;
    default:
        assert(false);
    }

    return answer;
}

bool answer(const char *question, int *result)
{
    assert(NULL != question);
    assert(NULL != result);

    size_t length = strlen(question);
    if (length < 10 || strncmp(question, "What is", 7) != 0)
    {
        // "What is 5?"
        return false;
    }

    size_t copy_length = length - 9; // delete '?'
    char *question_copy = (char *)calloc(1, copy_length + 1);
    assert(NULL != question_copy);

    // Handle "What is"
    strncpy(question_copy, &question[8], copy_length);

    bool ret = true;
    char delim[] = " ";
    int answer = 0;
    size_t count = 0;

    // number 1
    int number1 = 0;
    char *substr = NULL;
    if ((substr = strtok(question_copy, delim)) == NULL || sscanf(substr, "%d", &number1) != 1)
    {
        ret = false;
    }
    else
    {
        for (substr = strtok(NULL, delim); substr != NULL; substr = strtok(NULL, delim))
        {
            // operations
            char operation = get_operation(substr, delim);
            if (0 == operation)
            {
                ret = false;
                break;
            }
            else if (' ' == operation)
            {
                if (0 == count)
                {
                    ret = true;
                    answer = number1;
                    break;
                }
                else
                {
                    ret = false;
                    break;
                }
            }

            // number 2
            int number2 = 0;
            if ((substr = strtok(NULL, delim)) == NULL || sscanf(substr, "%d", &number2) != 1)
            {
                ret = false;
                break;
            }

            answer = calculate(number1, number2, operation);
            number1 = answer;
            count++;
        }
    }

    free(question_copy);

    if (ret)
    {
        if (0 == count)
        {
            *result = number1;
        }
        else
        {
            *result = answer;
        }
    }

    return ret;
}
