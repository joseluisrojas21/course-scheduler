#ifndef COURSE_DATA_H
#define COURSE_DATA_H

typedef struct {
    char *crn;
    char *subject;
    char *course;
    char *creditHours;
    char *title;
    char *days;
    char *classStarts_H;
    char *classStarts_M;
    char *classEnds_H;
    char *classEnds_M;
    char *seminars;
    char *instructor;
    char *location;
} course_data;

#endif