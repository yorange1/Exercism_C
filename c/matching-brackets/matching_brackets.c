#include "matching_brackets.h"

#include <stddef.h>
#include <string.h>

static bool is_match(char right, char left)
{
    char expect_left;

    switch (right)
    {
    case '[':
        expect_left = ']';
        break;
    case '{':
        expect_left = '}';
        break;
    case '(':
        expect_left = ')';
        break;
    default:
        return false;
        break;
    }

    return (expect_left == left);
}

bool is_paired(const char *input)
{
    if (NULL == input)
    {
        return false;
    }

    size_t length = strlen(input);

    char stack[length];
    size_t sp = 0;

    for (size_t i = 0; i < length; i++)
    {
        if (input[i] == '(' || input[i] == '[' || input[i] == '{')
        {
            stack[sp++] = input[i];
        }
        else if (input[i] == ')' || input[i] == ']' || input[i] == '}')
        {
            if (sp == 0 || !is_match(stack[--sp], input[i]))
            {
                return false;
            }
        }
    }

    return (0 == sp);
}
