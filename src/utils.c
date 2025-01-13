#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "../include/coursedata.h"

#define BUFFER_SIZE 1024
#define PATH_MAX 4096
#define TRUE 1
#define FALSE 0

int debugType = -1;

int inRange(int low, int high, int find) {
    if (low > high) {
        int temp = low;
        low = high;
        high = temp;
    }
    return low <= find && find <= high;
}

char* upperCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
    return str;
}

int validateDayRanges(char *classDays, int numberOfDays, char *chosenDays) {
    int lengthOfClassDays = 0;
    for (size_t i = 0; i < strlen(classDays); i++) {
        if (classDays[i] != ' ') {
            lengthOfClassDays++;
        }
    }
    for (int i = 0; i < lengthOfClassDays; i++) {
        char currentDay = classDays[i];
        for (int j = 0; j < numberOfDays; j++) {
            if (currentDay == chosenDays[j]) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

int timeToMinutes(int hour, int minute) {
    return hour * 60 + minute;
}

int checkClassTimeOverlap(const course_data* course1, const course_data* course2) {
    int start1 = timeToMinutes(atoi(course1->classStarts_H), atoi(course1->classStarts_M));
    int end1 = timeToMinutes(atoi(course1->classEnds_H), atoi(course1->classEnds_M));
    int start2 = timeToMinutes(atoi(course2->classStarts_H), atoi(course2->classStarts_M));
    int end2 = timeToMinutes(atoi(course2->classEnds_H), atoi(course2->classEnds_M));

    return (end1 < start2 || end2 < start1);
}

void setDebug(int debug) {
    debugType = debug;
}

// Returns TRUE if the time ranges do not overlap
// Returns FALSE if the time ranges overlap
int validateTimeRange(const course_data* course1, const course_data* course2, int debug) {
    setDebug(debug);

    if (strstr(upperCase(course1->days), "ON") || strstr(upperCase(course2->days), "ON")) {
        if (debugType == 3) {
            printf("One or both courses are online, skipping time validation\n");
        }
        return TRUE;
    }

    int lengthOfClass1Days = 0;
    size_t daysLength1 = strlen(course1->days);
    for (size_t i = 0; i < daysLength1; i++) {
        if (course1->days[i] != ' ') {
            lengthOfClass1Days++;
        }
    }

    int lengthOfClass2Days = 0;
    size_t daysLength2 = strlen(course2->days);
    for (size_t i = 0; i < daysLength2; i++) {
        if (course2->days[i] != ' ') {
            lengthOfClass2Days++;
        }
    }

    if (lengthOfClass1Days == 0 || lengthOfClass2Days == 0) {
        printf("Error: Empty days for one or both courses\n");
        printf("\nLength of class1: %d\n", lengthOfClass1Days);
        printf("Length of class2: %d\n", lengthOfClass2Days);
        exit(-1);
    }

    // Arrays to store the days
    char *class1Days[daysLength1];
    char *class2Days[daysLength2];

    // Day 1
    char copyOfDays1[daysLength1 + 1];
    strcpy(copyOfDays1, course1->days);
    copyOfDays1[strlen(copyOfDays1)] = ' ';

    int tokenNumber = 0;
    char *token = strtok(copyOfDays1, " ");
    while (token != NULL) {
        class1Days[tokenNumber] = token;
        tokenNumber++;
        token = strtok(NULL, " ");
    }

    // Day 2
    char copyOfDays2[strlen(course2->days) + 1];
    strcpy(copyOfDays2, course2->days);
    copyOfDays2[strlen(copyOfDays2)] = ' ';

    tokenNumber = 0;
    char *token2 = strtok(copyOfDays2, " ");
    while (token2 != NULL) {
        class2Days[tokenNumber] = token2;
        tokenNumber++;
        token2 = strtok(NULL, " ");
    }

    if (debugType == 3) {
        printf("Iterate over class1Days by %d | ", lengthOfClass1Days);
        for (int i = 0; i < lengthOfClass1Days; i++) {
            printf("%s", class1Days[i]);
        }
        printf("\n");
        printf("Iterate over class2Days by %d | ", lengthOfClass2Days);
        for (int i = 0; i < lengthOfClass2Days; i++) {
            printf("%s", class2Days[i]);
        }
        printf("\n");
    }

    // Compare class days to check for conflicts
    int conflictFound = FALSE;
    for (int i = 0; i < lengthOfClass1Days; i++) {
        for (int j = 0; j < lengthOfClass2Days; j++) {
            if (strcmp(class1Days[i], class2Days[j]) == 0) {
                conflictFound = TRUE;
                break;
            }
        }
        if (conflictFound) {
            break;
        }
    }

    if (conflictFound) {
        int result = checkClassTimeOverlap(course1, course2);
        if (debugType == 3 && result == 0) {
            printf("Time conflict detected on matching day\n");
            printf("%s:%s%s:%s\n", course1->classStarts_H, course1->classStarts_M, course1->classEnds_H, course1->classEnds_M);
            printf("%s:%s %s:%s\n", course2->classStarts_H, course2->classStarts_M, course2->classEnds_H, course2->classEnds_M);
        } else if (debugType == 3){
            printf("No time conflict detected on matching day\n");
            printf("%s:%s%s:%s\n", course1->classStarts_H, course1->classStarts_M, course1->classEnds_H, course1->classEnds_M);
            printf("%s:%s%s:%s\n", course2->classStarts_H, course2->classStarts_M, course2->classEnds_H, course2->classEnds_M);
        }
        return result;
    } else {
        if (debugType == 3) {
            printf("No time conflict detected\n");
        }
        return TRUE;
    }
}

void clearScreen() {
    // ANSI escape code to clear the screen
    printf("\033[2J\033[H");
}

void getTimeRange(int *earliestHour, int *latestHour) {
    printf("\nEnter a time range\n");
    while (TRUE) {
        printf("\nEnter the starting hour for classes\n");
        while (TRUE) {
            char option[3];
            scanf("%s", option);

            *earliestHour = atoi(option);
            if (*earliestHour > 0) {
                break;
            } else {
                printf("\nEnter a valid hour\n");
            }
        }

        while (TRUE) {
            char option[3];
            printf("\nEnter the ending hour for classes\n");
            scanf("%s", option);

            *latestHour = atoi(option);
            if (*latestHour > 0) {
                break;
            } else {
                printf("\nEnter a valid hour\n");
            }
        }

        if (*earliestHour <= *latestHour) {
            break;
        } else {
            printf("\n\nEnter a valid time range\n");
        }
    }
}

void getMaxLengths(const course_data courses[], int countSubjects, 
                   int *maxLengthOfDays, int *maxLengthOfSubject, int *maxLengthOfTitle) {
    *maxLengthOfDays = 0;
    *maxLengthOfSubject = 0;
    *maxLengthOfTitle = 0;
    
    for (int i = 0; i < countSubjects; i++) {
        int lenDays = strlen(courses[i].days);
        int lenSubject = strlen(courses[i].subject);
        int lenTitle = strlen(courses[i].title);

        if (lenDays > *maxLengthOfDays) {
            *maxLengthOfDays = lenDays;
        }
        if (lenSubject > *maxLengthOfSubject) {
            *maxLengthOfSubject = lenSubject;
        }
        if (lenTitle > *maxLengthOfTitle) {
            *maxLengthOfTitle = lenTitle;
        }
    }
}

void printCourseDetails(const course_data courses[], int countSubjects) {
    int maxLengthOfDays = 0;
    int maxLengthOfSubject = 0;
    int maxLengthOfTitle = 0;

    getMaxLengths(courses, countSubjects, &maxLengthOfDays, &maxLengthOfSubject, &maxLengthOfTitle);

    for (int i = 0; i < countSubjects; i++) {
        printf("%-6s %-*s  %-*s  %-*s %-2s:%-2s - %-2s:%-2s\n",
            courses[i].crn,
            maxLengthOfSubject, courses[i].subject,
            maxLengthOfTitle, courses[i].title,
            maxLengthOfDays, courses[i].days,
            courses[i].classStarts_H, courses[i].classStarts_M,
            courses[i].classEnds_H, courses[i].classEnds_M);
    }
    printf("\n");
}

void saveCourseDetails(const course_data courses[], int countSubjects, FILE *file) {
    int maxLengthOfDays = 0;
    int maxLengthOfSubject = 0;
    int maxLengthOfTitle = 0;

    getMaxLengths(courses, countSubjects, &maxLengthOfDays, &maxLengthOfSubject, &maxLengthOfTitle);

    for (int i = 0; i < countSubjects; i++) {
        fprintf(file, "%-6s %-*s  %-*s  %-*s %-2s:%-2s - %-2s:%-2s\n",
            courses[i].crn,
            maxLengthOfSubject, courses[i].subject,
            maxLengthOfTitle, courses[i].title,
            maxLengthOfDays, courses[i].days,
            courses[i].classStarts_H, courses[i].classStarts_M,
            courses[i].classEnds_H, courses[i].classEnds_M);
    }
    fprintf(file, "\n");
}

int getNumberOfDays() {
    int daysOfTheWeek = 6;
    int numberOfDays;
    while (TRUE) {
        printf("\nHow many days do you plan to attend school\n");
        char inputedDays[3];
        while (TRUE) {
            scanf("%s", inputedDays);
            if (atoi(inputedDays) > 0) {
                break;
            } else {
                printf("\nEnter a valid number of days\n");
            }
        }

        numberOfDays = atoi(inputedDays);
        printf("\n");

        if (numberOfDays <= daysOfTheWeek) {
            break;
        } else {
            printf("\nThe selected number of days must not exceed %d\n", daysOfTheWeek);
        }
    }
    return numberOfDays;
}

void getChosenDays(char chosenDays[], int numberOfDays) {
    printf("\nEnter the specific days you would like to attend\n");
    printf("(M)onday (T)uesday (W)ednesday Thu(R)day (F)riday (S)aturday\n");
    printf("\n");

    int daysLeft = numberOfDays - 1;
    for (int i = 0; i < numberOfDays; i++) {
        printf("Enter a day: ");
        scanf(" %c", &chosenDays[i]);
        if (islower(chosenDays[i])) {
            chosenDays[i] = toupper(chosenDays[i]);
        }
        getchar(); // consume the newline character
        if (daysLeft > 0) {
            printf("Days left to enter: %d\n", daysLeft--);
        }
    }
    chosenDays[numberOfDays] = '\0';
}

char** getChosenCRNs(int *numberOfCRNs) {
    while (TRUE) {
        printf("\nEnter the number of CRNs you want to include: ");
        char crns[3];
        scanf("%s", crns);

        *numberOfCRNs = atoi(crns);
        if (*numberOfCRNs > 0) {
            break;
        } else {
            printf("\nEnter a number\n");
        }
    }

    char **chosenCRNs = (char **)malloc(*numberOfCRNs * sizeof(char *));
    if (chosenCRNs == NULL) {
        printf("Memory allocation failed, exiting\n");
        exit(-1);
    }

    printf("\nEnter the CRNs\n");
    for (int i = 0; i < *numberOfCRNs; i++) {
        char input[8];

        while (TRUE) {
            printf("CRN %d: ", i + 1);
            scanf("%7s", input);

            if (strlen(input) != 5) {
                printf("\nThe CRN should be a 5 digit number\n");
            } else {
                break;
            }
        }

        chosenCRNs[i] = (char *)malloc(6 * sizeof(char));

        if (chosenCRNs[i] == NULL) {
            printf("Memory allocation failed, exiting\n");
            exit(-1);
        }
        strcpy(chosenCRNs[i], input);
    }
    return chosenCRNs;
}

void saveToFile(int countSchedules, int countSubjects, int position[], course_data **possibleSchedules) {
    printf("\nDo you want to save this in a txt file? (Y/N)\n");
    char option[3];
    scanf("%2s", option);

    // Convert input to uppercase
    for (int i = 0; option[i]; i++) {
        option[i] = toupper(option[i]);
    }

    if (strstr(option, "Y") != NULL) {
        printf("\nEnter a name for the file\n");
        char filename[105];
        scanf("%99s", filename);
        strcat(filename, ".txt");

        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            printf("\nThere was an error when trying to make the file %s\n", filename);
            exit(-1);
        }

        for (int row = 0; row < countSchedules; row++) {
            saveCourseDetails(possibleSchedules[position[row]], countSubjects, file);
        }

        fclose(file);
    }
    printf("\n");
    clearScreen();
}

char *strsep(char **stringp, const char *delim) {
    char *rv = *stringp;
    if (rv) {
        *stringp += strcspn(*stringp, delim);
        if (**stringp)
            *(*stringp)++ = '\0';
        else
            *stringp = 0; }
    return rv;
}

char* parseField(char **line, const char *delim) {
    char *field = strsep(line, delim);
    if (field && *field != '\0') {
        return strdup(field);
    }
    return "";
}

int countCoursesInCSV(const char *filename) {
    FILE *fileScnr = fopen(filename, "r");
    if (fileScnr == NULL) {
        perror("\nError while opening the file.\n");
        exit(-1);
    }

    char buffer[BUFFER_SIZE];
    int numberOfCourses = 0;

    // Skip the header line if present
    if (fgets(buffer, sizeof(buffer), fileScnr) == NULL) {
        fclose(fileScnr);
        return 0;
    }

    // Count the remaining lines in the CSV file
    while (fgets(buffer, sizeof(buffer), fileScnr) != NULL) {
        numberOfCourses++;
    }

    fclose(fileScnr);

    return numberOfCourses;
}

int countNumberOfSeminars(const char *seminars) {
    if (seminars == NULL || seminars[0] == '\0') {
        return 0;
    }
    
    int numberOfSeminars = 0;
    size_t i = 0;
    
    // Skip leading spaces
    while (seminars[i] == ' ') {
        i++;
    }
    
    while (seminars[i] != '\0') {
        // Found a seminar (not a space)
        if (seminars[i] != ' ') {
            numberOfSeminars++;
            
            // Skip the whole seminar (non-space characters) and any spaces
            while (seminars[i] != '\0' && seminars[i] != ' ') {
                i++;
            }
            
            // Skip any spaces between seminars
            while (seminars[i] == ' ') {
                i++;
            }
        } else {
            i++;
        }
    }
    return numberOfSeminars;
}

char* expandHomeDirectory(const char* path) {
    // Check if the path starts with ~
    if (path[0] == '~') {
        const char* home = getenv("HOME");
        if (home == NULL) {
            fprintf(stderr, "Error: HOME environment variable is not set.\n");
            exit(EXIT_FAILURE);
        }

        // Allocate memory for the expanded path (home + remaining part of the path)
        size_t homeLength = strlen(home);
        size_t pathLength = strlen(path);

        // Allocate memory for the new path
        char* expandedPath = (char*)malloc(homeLength + pathLength);
        if (expandedPath == NULL) {
            fprintf(stderr, "Error: Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }

        // Copy the home directory part and then the rest of the path
        strcpy(expandedPath, home);
        strcpy(expandedPath + homeLength, path + 1); // Skip the '~' character

        return expandedPath;
    } else {
        return strdup(path);
    }
}

char* resolvePath(const char* path) {
    // Allocate memory for the resolved path
    char* resolvedPath = (char*)malloc(PATH_MAX);
    if (resolvedPath == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for resolved path.\n");
        exit(EXIT_FAILURE);
    }

    // Get the absolute path from the relative one
    if (realpath(path, resolvedPath) == NULL) {
        perror("Error resolving path");
        free(resolvedPath);
        exit(EXIT_FAILURE);
    }

    return resolvedPath;
}