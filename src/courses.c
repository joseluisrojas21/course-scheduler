#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/combination.h"
#include "../include/coursedata.h"
#include "../include/utils.h"

#define BUFFER_SIZE 1024
#define TRUE 1
#define FALSE 0

void viewCourses(course_data courses[], int numberOfCourses) {
    for(int index = 0; index < numberOfCourses; index++) {
        printf("CRN: %s\n",courses[index].crn);
        printf("Subject: %s\n", courses[index].subject);
        printf("Course: %s\n", courses[index].course);
        printf("Credit Hours: %s\n", courses[index].creditHours);
        printf("Title: %s\n", courses[index].title);
        printf("Days: %s\n", courses[index].days);
        printf("Time: %s:%s - %s:%s\n", courses[index].classStarts_H,
            courses[index].classStarts_M, courses[index].classEnds_H,
            courses[index].classEnds_M);
        printf("Instructor: %s\n", courses[index].instructor);
        printf("Location: %s\n", courses[index].location);
        printf("-------------------------------------------------------\n");
    }
}

void searchCourses(course_data *courses, int numberOfCourses,
                    const char *searchCriterion, const char *searchValue) {
    int found = FALSE;
    printf("\n-------------------------------------------------------\n");
    for (int index = 0; index < numberOfCourses; index++) {
        int match = 0;
        if (strcmp(searchCriterion, "CRN") == 0 &&
            strcmp(courses[index].crn, searchValue) == 0) {
            match = TRUE;
        } else if (strcmp(searchCriterion, "Subject") == 0 &&
                    strcasecmp(courses[index].subject, searchValue) == 0) {
            match = TRUE;
        } else if (strcmp(searchCriterion, "Course") == 0 &&
                    strcmp(courses[index].course, searchValue) == 0) {
            match = TRUE;
        } else if (strcmp(searchCriterion, "Title") == 0 &&
                    strcmp(courses[index].title, searchValue) == 0) {
            match = TRUE;
        } else if (strcmp(searchCriterion, "Instructor") == 0 &&
                    strcmp(courses[index].instructor, searchValue) == 0) {
            match = TRUE;
        }

        if (match) {
            printf("CRN: %s\n",courses[index].crn);
            printf("Subject: %s\n", courses[index].subject);
            printf("Course: %s\n", courses[index].course);
            printf("Credit Hours: %s\n", courses[index].creditHours);
            printf("Title: %s\n", courses[index].title);
            printf("Days: %s\n", courses[index].days);
            printf("Time: %s:%s - %s:%s\n", courses[index].classStarts_H,
                courses[index].classStarts_M, courses[index].classEnds_H,
                courses[index].classEnds_M);
            printf("Instructor: %s\n", courses[index].instructor);
            printf("Location: %s\n", courses[index].location);
            printf("-------------------------------------------------------\n");
            found = TRUE;
        }
    }
    if (!found) {
        printf("No class found with %s: %s\n", searchCriterion, searchValue);
    }
    printf("\n");
}

void search(course_data *courses, int numberOfCourses) {
    while (TRUE) {
        printf("1. Search by CRN\n");
        printf("2. Search by subject\n");
        printf("3. Search by course\n");
        printf("4. Search by title\n");
        printf("5. Search by instructor\n");
        printf("6. Go back\n \n");

        char option[2];
        scanf("%s", option);

        char searchValue[BUFFER_SIZE];
        const char *searchCriterion = NULL;

        if (strcmp(option, "1") == 0) {
            searchCriterion = "CRN";
        } else if (strcmp(option, "2") == 0) {
            searchCriterion = "Subject";
        } else if (strcmp(option, "3") == 0) {
            searchCriterion = "Course";
        } else if (strcmp(option, "4") == 0) {
            searchCriterion = "Title";
        } else if (strcmp(option, "5") == 0) {
            searchCriterion = "Instructor";
        } else if (strcmp(option, "6") == 0) {
            break;
        } else {
            printf("\nSelect a valid option\n\n");
            continue;
        }

        printf("Type the %s\n", searchCriterion);
        scanf("%s", searchValue);

        searchCourses(courses, numberOfCourses, searchCriterion, searchValue);
    }
}

void menu(course_data courses[], int numberOfCourses, int debug) {
    printf("1. View all data from all courses\n");
    printf("2. View all possible schedules\n");
    printf("3. Search in the file\n");
    printf("4. Exit\n \n");

    char option[2];
    scanf("%s", option);

    if (!strcmp(option,"1")) {
        printf("\n");
        printf("-------------------------------------------------------\n");
        clearScreen();
        viewCourses(courses, numberOfCourses);
        printf("\n");
    } else if (!strcmp(option,"2")) {
        clearScreen();
        dataProcessor(courses, numberOfCourses, debug);
        printf("\n");
    } else if (!strcmp(option,"3")) {
        printf("\n");
        clearScreen();
        search(courses, numberOfCourses);
        printf("\n");
    } else if (!strcmp(option,"4")) {
        exit(0);
    } else {
        printf("\nSelect a valid option\n\n");
    }
}

course_data parseCourseData(char *line) {
    course_data course = {0};

    if (line == NULL) {
        fprintf(stderr, "Error: NULL line passed to parseCourseData.\n");
        exit(-1);
    }

    // Parse CRN
    course.crn = parseField(&line, ",");
    if (course.crn == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for CRN.\n");
        exit(-1);
    }

    // Parse Subject
    course.subject = parseField(&line, ",");
    if (course.subject == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for Subject.\n");
        exit(-1);
    }

    // Parse Course
    course.course = parseField(&line, ",");
    if (course.course == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for Course.\n");
        exit(-1);
    }

    // Parse Credit Hours
    course.creditHours = parseField(&line, ",");
    if (course.creditHours == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for Credit Hours.\n");
        exit(-1);
    }

    // Parse Title
    course.title = parseField(&line, ",");
    if (course.title == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for Title.\n");
        exit(-1);
    }

    // Parse Days
    course.days = parseField(&line, ",");
    if (course.days == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for Days.\n");
        exit(-1);
    }

    // Parse Class Start Hour (HH)
    course.classStarts_H = parseField(&line, ":");
    if (course.classStarts_H == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for Class Start Hour.\n");
        exit(-1);
    }

    // Parse Class Start Minute (MM)
    course.classStarts_M = parseField(&line, "-");
    if (course.classStarts_M == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for Class Start Minute.\n");
        exit(-1);
    }

    // Parse Class End Hour (HH)
    course.classEnds_H = parseField(&line, ":");
    if (course.classEnds_H == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for Class End Hour.\n");
        exit(-1);
    }

    // Parse Class End Minute (MM)
    course.classEnds_M = parseField(&line, ",");
    if (course.classEnds_M == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for Class End Minute.\n");
        exit(-1);
    }

    // Parse Seminars
    course.seminars = parseField(&line, ",");
    if (course.seminars == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for Seminars.\n");
        exit(-1);
    }

    // Parse Instructor
    course.instructor = parseField(&line, ",");
    if (course.instructor == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for Instructor.\n");
        exit(-1);
    }

    // Parse Location
    course.location = parseField(&line, ",");
    if (course.location == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for Location.\n");
        exit(-1);
    }
    return course;
}

int areSeminarsDuplicate(char *seminars1, char *seminars2, int row1, int row2) {
    int duplicateFound = FALSE;
    int numberOfSeminars1 = countNumberOfSeminars(seminars1);
    int numberOfSeminars2 = countNumberOfSeminars(seminars2);

    if (countNumberOfSeminars(seminars1) == 0 || countNumberOfSeminars(seminars2) == 0) {
        return FALSE;
    }

    // Seminar 1
    char *seminarArray1[numberOfSeminars1];
    char copyOfSeminars1[strlen(seminars1) + 1];
    strcpy(copyOfSeminars1, seminars1);
    copyOfSeminars1[strlen(copyOfSeminars1)] = ' ';

    int tokenNumber = 0;
    char *seminar1 = strtok(copyOfSeminars1, " ");
    while (seminar1 != NULL) {
        seminarArray1[tokenNumber] = seminar1;
        tokenNumber++;
        seminar1 = strtok(NULL, " ");
    }

    // Seminar 2
    char *seminarArray2[numberOfSeminars2];
    char copyOfSeminars2[strlen(seminars2) + 1];
    strcpy(copyOfSeminars2, seminars2);
    copyOfSeminars2[strlen(copyOfSeminars2)] = ' ';

    tokenNumber = 0;
    char *seminar2 = strtok(copyOfSeminars2, " ");
    while (seminar2 != NULL) {
        seminarArray2[tokenNumber] = seminar2;
        tokenNumber++;
        seminar2 = strtok(NULL, " ");
    }

    for (int i = 0; i < numberOfSeminars1; i++) {
        // Check for duplicates within seminarArray1
        for (int j = i + 1; j < numberOfSeminars1; j++) {
            if (strcmp(seminarArray1[i], seminarArray1[j]) == 0) {
                printf("Duplicate Seminar %s\n", seminarArray1[i]);
                printf("\nOn columns %d and %d \n\n", i + 1, j + 1);
                duplicateFound = TRUE;
            }
        }

        // Check for duplicates across seminarArray1 and seminarArray2
        for (int j = 0; j < numberOfSeminars2; j++) {
            if (strcmp(seminarArray1[i], seminarArray2[j]) == 0) {
                printf("Duplicate Seminar %s\n", seminarArray1[i]);
                printf("\nDuplicated on these seminars\n%s\n%s\n", seminars1, seminars2);
                printf("\nOn columns %d and %d \n", i + 1, j + 1);
                printf("On rows %d and %d \n\n", row1 + 2, row2 + 2);
                duplicateFound = TRUE;
            }
        }
    }

    for (int i = 0; i < numberOfSeminars2; i++) {
        // Check for duplicates within seminarArray2
        for (int j = i + 1; j < numberOfSeminars2; j++) {
            if (strcmp(seminarArray2[i], seminarArray2[j]) == 0) {
                printf("Duplicate Seminar %s\n", seminarArray2[i]);
                printf("\nOn columns %d and %d \n\n", i + 1, j + 1);
                duplicateFound = TRUE;
            }
        }
    }

    return duplicateFound;
}

void checkForDuplicates(course_data *courses, int size) {
    int duplicateFound = FALSE;
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (strcmp(courses[i].crn, courses[j].crn) == 0) {
                printf("Duplicate CRN found: %s\n", courses[i].crn);
                printf("On rows: %d and %d\n", i+2, j+2);
                duplicateFound = TRUE;
            }
            if (strlen(courses[i].seminars) >= 1 && strlen(courses[j].seminars) >= 1) {
                // printf("%s AND %s\n", courses[i].seminars, courses[j].seminars);
                if (areSeminarsDuplicate(courses[i].seminars, courses[j].seminars, i, j)) {
                    duplicateFound = TRUE;
                }
            }
        }
    }
    if (duplicateFound) {
        exit(0);
    }
}

void loadData(int debug, const char* filename) {
    char* expandedFilename = expandHomeDirectory(filename);

    char* resolvedFilename = resolvePath(expandedFilename);
    free(expandedFilename);

    int numberOfCourses = countCoursesInCSV(resolvedFilename);
    if (numberOfCourses == 0) {
        fprintf(stderr, "Error: Invalid number of courses (%d).\n", numberOfCourses);
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(resolvedFilename, "r");
    if (file == NULL) {
        printf("\nError while opening %s file\n", resolvedFilename);
        free(resolvedFilename);
        exit(-1);
    }

    course_data courses[numberOfCourses];

    size_t length = BUFFER_SIZE;
    char *line = (char *) malloc (length);
    if (line == NULL) {
        printf("\nError while allocating memory for line\n");
        free(resolvedFilename);
        fclose(file);
        exit(-1);
    }

    // Skip the first line
    if (getline(&line, &length, file) == -1) {
        fprintf(stderr, "Error: Unable to read the header line from the file.\n");
        free(line);
        fclose(file);
        free(resolvedFilename);
        exit(EXIT_FAILURE);
    }

    int row = 0;
    while ((getline(&line, &length, file) != -1)) {
        courses[row] = parseCourseData(line);
        row++;
    }

    free(line);
    fclose(file);
    free(resolvedFilename);
    printf("\n");

    checkForDuplicates(courses, numberOfCourses);
    clearScreen();
    menu(courses, numberOfCourses, debug);
}
