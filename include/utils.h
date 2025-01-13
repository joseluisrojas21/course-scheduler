#ifndef utils_H
#define utils_H

#include "coursedata.h"

int inRange(int low, int high, int find);

char *upperCase(char *arr);

int validateDayRanges(
    char *classDays,
    int numberOfDays,
    char *chosenDays
);

int validateTimeRange(
    const course_data* course1,
    const course_data* course2,
    int debug
);

int checkClassTimeOverlap(const course_data* course1, const course_data* course2);

void clearScreen();

void getTimeRange(int *earliestHour, int *latestHour);

void getMaxLengths(
    const course_data courses[],
    int countSubjects,
    int *maxLengthOfDays,
    int *maxLengthOfSubject,
    int *maxLengthOfTitle
);

void printCourseDetails(const course_data courses[], int countSubjects);

void saveCourseDetails(const course_data courses[], int countSubjects, FILE *file);

int getNumberOfDays();

void getChosenDays(char chosenDays[], int numberOfDays);

char** getChosenCRNs(int *numberOfCRNs);

void saveToFile(int countSchedules, int countSubjects, int position[], course_data **possibleSchedules);

char *strsep(char **stringp, const char *delim);

char* parseField(char **line, const char *delim);

int countCoursesInCSV(const char *filename);

int countNumberOfSeminars(const char *seminars);

char* expandHomeDirectory(const char* path);

char* resolvePath(const char* path);

#endif