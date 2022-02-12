#include "secret_handshake.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// 1 = wink
// 10 = double blink
// 100 = close your eyes
// 1000 = jump
// 10000 = Reverse the order of the operations in the secret handshake.

#define CMD_WINK (0x01)
#define CMD_DOBULE (0x02)
#define CMD_CLOSE (0x04)
#define CMD_JUMP (0x08)
#define CMD_REVERSE (0x10)
#define CMD_MAX (0x1F)
#define CMD_STR_LEN (20)

const char **commands(size_t number)
{
    char cmd_table[4][CMD_STR_LEN + 1] = {
        "wink",
        "double blink",
        "close your eyes",
        "jump",
    };

    size_t count = 0;
    char tmp[4][CMD_STR_LEN + 1] = {0};

    for (size_t i = 0; i < 4; i++)
    {
        size_t bit = 1 << i;
        if ((number & bit) != 0)
        {
            strncpy(tmp[count], cmd_table[i], CMD_STR_LEN);
            count++;
        }
    }

    char **cmds = (char **)calloc(count, sizeof(const char *));

    if (0 == count)
        return (const char**)cmds;

    if ((number & CMD_REVERSE) != 0)
    {
        for (size_t i = 0; i < count; i++)
        {
            size_t table_index = count - 1 - i;
            cmds[i] = (char *)calloc(1, strlen(tmp[table_index] + 1));
            strncpy(cmds[i], tmp[table_index], CMD_STR_LEN);
        }
    }
    else
    {
        for (size_t i = 0; i < count; i++)
        {
            cmds[i] = (char *)calloc(1, strlen(tmp[i] + 1));
            strncpy(cmds[i], tmp[i], CMD_STR_LEN);
        }
    }

    return (const char**)cmds;
}
