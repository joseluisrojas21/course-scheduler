#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#include "../include/coursedata.h"
#include "../include/utils.h"

#define TRUE 1
#define FALSE 0

void displayMenu() {
    printf("1. View all possible schedules\n");
    printf("2. View schedules within a specific time range\n");
    printf("3. View schedules within a specific time range on selected days\n");
    printf("4. View schedules containing a specific number of CRNs\n");
    printf("5. View schedules within a specific time range, containing a specific number of CRNs, on selected days\n");
    printf("6. Go back\n");
    printf("7. Exit\n");
}

void handleOption1(int countPossibleSchedules, course_data **possibleSchedules, int countSubjects) {
    printf("----------------------------------------------------------------------------------\n");
    for (int row = 0; row < countPossibleSchedules; row++) {
        printCourseDetails(possibleSchedules[row], countSubjects);
    }
    printf("----------------------------------------------------------------------------------\n");

    printf("\nDo you want to save this in a txt file?\n");
    char option[3];
    scanf("%s", option);
    
    if (strstr(upperCase(option), "Y") != NULL) {
        printf("\nEnter a name for the file\n");
        char filename[105];
        scanf("%99s", filename);
        strcat(filename, ".txt");

        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            printf("\nThere was an error when trying to make the file %s\n", filename);
            exit(-1);
        }

        for (int row = 0; row < countPossibleSchedules; row++) {
            saveCourseDetails(possibleSchedules[row], countSubjects, file);
        }

        fclose(file);
    }

    clearScreen();
}

void handleOption2(int countPossibleSchedules, course_data **possibleSchedules, int countSubjects) {
    int earliestHour;
    int latestHour;
    getTimeRange(&earliestHour, &latestHour);

    printf("\n");
    printf("----------------------------------------------------------------------------------\n");

    course_data tempCourses[countSubjects];
    int position[countPossibleSchedules];
    int countSchedules = 0;
    int found = FALSE;
    for (int row = 0; row < countPossibleSchedules; row++) {
        int numberOfPossibleClasses = 0;
        int numberOfAllClasses = 0;
        for (int column = 0; column < countSubjects; column++) {
            tempCourses[column] = possibleSchedules[row][column];
            int classStartHR = atoi(tempCourses[column].classStarts_H);
            int classEndsHR = atoi(tempCourses[column].classEnds_H);

            if (inRange(earliestHour, latestHour, classStartHR) && inRange(earliestHour, latestHour, classEndsHR)) {
                numberOfPossibleClasses++;
            }
            numberOfAllClasses++;
        }

        if (numberOfPossibleClasses == numberOfAllClasses) {
            printCourseDetails(tempCourses, countSubjects);
            position[countSchedules] = row;
            countSchedules++;
            found = TRUE;
        } else if (row == countPossibleSchedules - 1 && found == FALSE) {
            printf("No schedules found!\n");
        }
    }
    printf("----------------------------------------------------------------------------------\n");
    printf("\n");

    if (found == TRUE) {
        saveToFile(countSchedules, countSubjects, position, possibleSchedules);
    }
}

void handleOption3(int countPossibleSchedules, course_data **possibleSchedules, int countSubjects) {
    int earliestHour;
    int latestHour;
    getTimeRange(&earliestHour, &latestHour);

    int numberOfDays = getNumberOfDays();
    char chosenDays[numberOfDays+1];

    getChosenDays(chosenDays, numberOfDays);

    printf("\n");
    printf("----------------------------------------------------------------------------------\n");

    course_data tempCourses[countSubjects];
    int position[countPossibleSchedules];
    int countSchedules = 0;
    int found = FALSE;
    for(int row = 0; row < countPossibleSchedules; row++) {
        int numberOfPossibleClasses = 0;
        int numberOfAllClasses = 0;
        for (int column = 0; column < countSubjects; column++) {
            tempCourses[column] = possibleSchedules[row][column];

            int classStartHR = atoi(tempCourses[column].classStarts_H);
            int classEndsHR = atoi(tempCourses[column].classEnds_H);
            char *days = tempCourses[column].days;

            if (strstr(upperCase(days), "ON") != NULL) {
                numberOfPossibleClasses++;
            } else if (inRange(earliestHour, latestHour, classStartHR)
                    && inRange(earliestHour, latestHour, classEndsHR)
                    && validateDayRanges(days, numberOfDays, chosenDays)) {
                numberOfPossibleClasses++;
            }
            numberOfAllClasses++;
        }

        if (numberOfPossibleClasses == numberOfAllClasses) {
            printCourseDetails(tempCourses, countSubjects);
            position[countSchedules] = row;
            countSchedules++;
            found = TRUE;
        } else if (row == countPossibleSchedules-1 && found == FALSE) {
            printf("No schedules found!\n");
        }
    }
    printf("----------------------------------------------------------------------------------\n");
    printf("\n");

    if (found == TRUE) {
        saveToFile(countSchedules, countSubjects, position, possibleSchedules);
    }
}

void handleOption4(int countPossibleSchedules, course_data **possibleSchedules, int countSubjects) {
    int numberOfCRNs = 0;
    char **chosenCRNs = getChosenCRNs(&numberOfCRNs);

    printf("\n");
    printf("----------------------------------------------------------------------------------\n");
    course_data tempCourses[countSubjects];
    int position[countPossibleSchedules];
    int countSchedules = 0;
    int found = FALSE;
    for(int row = 0; row < countPossibleSchedules; row++) {
        int crnsMatched = 0;
        for (int column = 0; column < countSubjects; column++) {
            tempCourses[column] = possibleSchedules[row][column];

            for (int i = 0; i < numberOfCRNs; i++) {
                if (!strcmp(tempCourses[column].crn, chosenCRNs[i])) {
                    crnsMatched++;
                }
            }
        }

        if (crnsMatched == numberOfCRNs) {
            printCourseDetails(tempCourses, countSubjects);
            position[countSchedules] = row;
            countSchedules++;
            found = TRUE;
        } else if (row == countPossibleSchedules-1 && found == FALSE) {
            printf("No schedules found!\n");
        }
    }
    printf("----------------------------------------------------------------------------------\n");
    printf("\n");

    if (found == TRUE) {
        saveToFile(countSchedules, countSubjects, position, possibleSchedules);
    }

    for (int i = 0; i < numberOfCRNs; i++) {
        free(chosenCRNs[i]);
    }
}

void handleOption5(int countPossibleSchedules, course_data **possibleSchedules, int countSubjects) {
    int earliestHour;
    int latestHour;
    getTimeRange(&earliestHour, &latestHour);

    int numberOfDays = getNumberOfDays();
    char chosenDays[numberOfDays+1];
    getChosenDays(chosenDays, numberOfDays);

    int numberOfCRNs = 0;
    char **chosenCRNs = getChosenCRNs(&numberOfCRNs);

    printf("\n");
    printf("----------------------------------------------------------------------------------\n");

    course_data tempCourses[countSubjects];
    int position[countPossibleSchedules];
    int countSchedules = 0;
    int found = FALSE;

    for(int row = 0; row < countPossibleSchedules; row++) {
        int numberOfPossibleClasses = 0;
        int numberOfAllClasses = 0;
        for (int column = 0; column < countSubjects; column++) {
            tempCourses[column] = possibleSchedules[row][column];

            int classStartHR = atoi(tempCourses[column].classStarts_H);
            int classEndsHR = atoi(tempCourses[column].classEnds_H);
            char *days = tempCourses[column].days;

            if (strstr(upperCase(days), "ON") != NULL) {
                numberOfPossibleClasses++;
            } else if (inRange(earliestHour, latestHour, classStartHR)
                    && inRange(earliestHour, latestHour, classEndsHR)
                    && validateDayRanges(days, numberOfDays, chosenDays)) {
                numberOfPossibleClasses++;
            }
            numberOfAllClasses++;
        }

        if (numberOfPossibleClasses == numberOfAllClasses) {
            position[countSchedules] = row;
            countSchedules++;
            found = TRUE;
        } else if (row == countPossibleSchedules-1 && found == FALSE) {
            printf("No schedules found!\n");
        }
    }

    found = FALSE;
    int position2[countSchedules];
    int countSchedules2 = 0;
    for(int row = 0; row < countSchedules; row++) {
        int crnsMatched = 0;
        for (int column = 0; column < countSubjects; column++) {
            tempCourses[column] = possibleSchedules[position[row]][column];

            for (int i = 0; i < numberOfCRNs; i++) {
                if (!strcmp(tempCourses[column].crn, chosenCRNs[i])) {
                    crnsMatched++;
                }
            }
        }

        if (crnsMatched == numberOfCRNs) {
            printCourseDetails(tempCourses, countSubjects);
            position2[countSchedules2] = row;
            countSchedules2++;
            found = TRUE;
        } else if (row == countPossibleSchedules-1 && found == FALSE) {
            printf("No schedules found!\n");
        }
    }

    printf("----------------------------------------------------------------------------------\n");
    printf("\n");

    if (found == TRUE) {
        saveToFile(countSchedules, countSubjects, position, possibleSchedules);
    }

    for (int i = 0; i < numberOfCRNs; i++) {
        free(chosenCRNs[i]);
    }
}

void handleOption6(int countPossibleSchedules, course_data **possibleSchedules) {
    for (int i = 0; i < countPossibleSchedules; i++) {
        free(possibleSchedules[i]);
    }
    free(possibleSchedules);
    clearScreen();
}

void handleOption7(int countPossibleSchedules, course_data **possibleSchedules) {
    for (int i = 0; i < countPossibleSchedules; i++) {
        free(possibleSchedules[i]);
    }
    free(possibleSchedules);
    exit(0);
}

void processSchedules(int countPossibleSchedules, course_data **possibleSchedules, int countSubjects) {
    while (TRUE) {
        displayMenu();
        
        char option[3];
        scanf("%s", option);

        // Handle the user's choice
        if (!strcmp(option, "1")) {
            handleOption1(countPossibleSchedules, possibleSchedules, countSubjects);
        } else if (!strcmp(option, "2")) {
            handleOption2(countPossibleSchedules, possibleSchedules, countSubjects);
        } else if (!strcmp(option, "3")) {
            handleOption3(countPossibleSchedules, possibleSchedules, countSubjects);
        } else if (!strcmp(option, "4")) {
            handleOption4(countPossibleSchedules, possibleSchedules, countSubjects);
        } else if (!strcmp(option, "5")) {
            handleOption5(countPossibleSchedules, possibleSchedules, countSubjects);
        } else if (!strcmp(option, "6")) {
            handleOption6(countPossibleSchedules, possibleSchedules);
            break;
        } else if (!strcmp(option, "7")) {
            handleOption7(countPossibleSchedules, possibleSchedules);
        } else {
            printf("Select a valid option\n\n");
        }
    }
}