#include "robot_simulator.h"

#include <string.h>

robot_status_t robot_create(robot_direction_t direction, int x, int y)
{
    robot_status_t status = {.direction = direction,
                             .position = {.x = x,
                                          .y = y}};

    return status;
}

static void robot_advance(robot_status_t *robot)
{
    switch (robot->direction)
    {
    case DIRECTION_NORTH:
        robot->position.y++;
        break;
    case DIRECTION_SOUTH:
        robot->position.y--;
        break;
    case DIRECTION_EAST:
        robot->position.x++;
        break;
    case DIRECTION_WEST:
        robot->position.x--;
        break;
    default:
        break;
    }
}

void robot_move(robot_status_t *robot, const char *commands)
{
    size_t commands_length = strlen(commands);

    for (size_t i = 0; i < commands_length; i++)
    {
        switch (commands[i])
        {
        case 'R':
            robot->direction = (robot_direction_t)((robot->direction + 1) % DIRECTION_MAX);
            break;
        case 'L':
            robot->direction = (robot_direction_t)((robot->direction + 3) % DIRECTION_MAX);
            break;
        case 'A':
            robot_advance(robot);
            break;
        default:
            break;
        }
    }
}