#include "grade_school.h"

#include <string.h>

void init_roster(roster_t *roster)
{
    roster->count = 0;
    memset(roster->students, 0, sizeof(roster->students));
}

bool add_student(roster_t *roster, const char *name, uint8_t grade)
{
    if (roster->count == 0)
    {
        roster->students[roster->count].grade = grade;
        strncpy(roster->students[roster->count].name, name, MAX_NAME_LENGTH);
        roster->count++;

        return true;
    }

    for (size_t i = 0; i < roster->count; i++)
    {
        student_t *stu = &roster->students[i];
        if (strncmp(stu->name, name, MAX_NAME_LENGTH) == 0)
        {
            return false;
        }
    }

    roster->students[roster->count].grade = grade;
    strncpy(roster->students[roster->count].name, name, MAX_NAME_LENGTH);
    roster->count++;

    for (int i = roster->count - 1; i >= 1; i--)
    {
        student_t* curr_stu = &roster->students[i];
        student_t* prev_stu = &roster->students[i - 1];

        if (curr_stu->grade < prev_stu->grade ||
           (curr_stu->grade == prev_stu->grade && strncmp(curr_stu->name, prev_stu->name, MAX_NAME_LENGTH) < 0))
        {
            student_t temp_stu;
            temp_stu.grade = prev_stu->grade;
            strncpy(temp_stu.name, prev_stu->name, MAX_NAME_LENGTH);

            prev_stu->grade = curr_stu->grade;
            strncpy(prev_stu->name, curr_stu->name, MAX_NAME_LENGTH);

            curr_stu->grade = temp_stu.grade;
            strncpy(curr_stu->name, temp_stu.name, MAX_NAME_LENGTH);
        }
    }

    return true;
}

roster_t get_grade(roster_t *roster, uint8_t desired_grade)
{
    roster_t desired_roster;
    init_roster(&desired_roster);

    for (size_t i = 0; i < roster->count; i++)
    {
        student_t *curr = &roster->students[i];
        if (curr->grade == desired_grade)
        {
            student_t *insert = &desired_roster.students[desired_roster.count];

            insert->grade = curr->grade;
            strncpy(insert->name, curr->name, MAX_NAME_LENGTH);

            desired_roster.count++;
        }
    }

    return desired_roster;
}
