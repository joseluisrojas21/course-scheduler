#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#include "../include/coursedata.h"
#include "../include/queue.h"
#include "../include/scheduleoptions.h"
#include "../include/utils.h"

#define TRUE 1
#define FALSE 0

typedef struct {
    int maxCombinations;
    int maxCourseOptions;
    Queue* positionQueue;
} CombinationData;

int typeOfDebug = -1;

void setDebugLevel(int debug) {
    typeOfDebug = debug;
}

void printSubjectDetails(const char *subjects[], const char *titles[], int repeatedCourses[],
                        int countSubjects, int creditHours[]) {
    int totalCreditHours = 0;
    int maxLengthOfTitle = 0;
    int maxLengthOfSubject = 0;

    for (int i = 0; i < countSubjects; i++) {
        int titleLength = strlen(titles[i]);
        int subjectLength = strlen(subjects[i]);
    
        if (titleLength > maxLengthOfTitle) {
            maxLengthOfTitle = titleLength;
        }
        if (subjectLength > maxLengthOfSubject) {
            maxLengthOfSubject = subjectLength;
        }
    }

    for (int i = 0; i < countSubjects; i++) {
        printf("%-*s %-*s: %d courses\n",
        maxLengthOfSubject, subjects[i],
        maxLengthOfTitle, titles[i], repeatedCourses[i]);
        totalCreditHours += creditHours[i];
    }

    printf("\nTotal number of subjects: %d\n", countSubjects);
    printf("Total credit hours: %d\n", totalCreditHours);
}

int compareCourses(const void *a, const void *b) {
    return strcmp(((course_data *)a)->title, ((course_data *)b)->title);
}

int countDistinctSubjects(course_data courses[], int numberOfCourses) {
    if (numberOfCourses == 0) return 0;
    qsort(courses, numberOfCourses, sizeof(course_data), compareCourses);
    int uniqueSubjectCount = 0;
    for (int i = 0; i < numberOfCourses; i++) {
        if (i == 0 || strcmp(courses[i].title, courses[i - 1].title) != 0) {
            uniqueSubjectCount++;
        }
    }
    return uniqueSubjectCount;
}

int countRepeatedCourses(course_data courses[], int numberOfCourses, 
                        const char *searchTitle) {
    if (searchTitle == NULL) {
        return -1;
    }

    int occurrenceCount = 0;
    for (int i = 0; i < numberOfCourses; i++) {
        if (!strcmp(courses[i].title, searchTitle)) {
            occurrenceCount++;
        }
    }
    return occurrenceCount;
}

int findSeminars(char *seminars, const char *CRN) {
    if (!seminars || !CRN) {
        return FALSE;
    }

    char copy[strlen(seminars) + 1];
    strcpy(copy, seminars);

    char *token = strtok(copy, " ");
    while (token) {
        if (strcmp(CRN, token) == 0) {
            return TRUE;
        }
        token = strtok(NULL, " ");
    }

    return FALSE;
}

int hasSeminars(const course_data courses[], int numberOfCourses) {
    for(int i = 0; i < numberOfCourses; i++) {
        // Check if the length of seminars is greater than 5 (indicating more than 1 seminar)
        if (strlen(courses[i].seminars) >= 5) {
            return TRUE;
        }
    }
    return FALSE;
}

void enqueueInt(Queue* queue, int position) {
    int* positionToEnqueue = (int*)malloc(sizeof(int));
    *positionToEnqueue = position;
    enqueue(queue, positionToEnqueue);
}

int dequeueInt(Queue* queue) {
    int* positionToRetrieve = (int*)dequeue(queue);
    if (positionToRetrieve != NULL) {
        int position = *positionToRetrieve;
        free(positionToRetrieve);
        return position;
    }
    return -1;
}

CombinationData initializeCombination(int repeatedCourses[], int countSubjects) {
    CombinationData data = {1, 0, makeQueue()};
    if (!data.positionQueue) {
        printf("Could not allocate memory for positionQueue\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < countSubjects; i++) {
        data.maxCombinations *= repeatedCourses[i];
        if (repeatedCourses[i] > data.maxCourseOptions) {
            data.maxCourseOptions = repeatedCourses[i];
        }
    }
    return data;
}

int isSeminarMatch(const course_data* course1, const course_data* course2) {
    return findSeminars(course1->seminars, course2->crn) || 
           findSeminars(course2->seminars, course1->crn);
}

int isValidSchedule(int isSeminar, int seminarCheck,
                    int numberOfPossibleClasses, int numberOfAllClasses) {
    return (isSeminar && seminarCheck && numberOfPossibleClasses == numberOfAllClasses) ||
           (!isSeminar && numberOfPossibleClasses == numberOfAllClasses);
}

void validateSchedule(const course_data** generatedSchedule, CombinationData data, 
                      int *countPossibleSchedules, int countSubjects, int isSeminar, 
                      int numberOfAllClasses, int row) {
    
    int numberOfPossibleClasses = 0;
    int dontContinue = FALSE;
    int seminarCheck = FALSE;

    if (typeOfDebug == 1 || typeOfDebug == 3) {
        printf("\n%d\n", row);
    }

    for (int i = 0; i < countSubjects - 1; i++) {
        for (int j = i + 1; j < countSubjects; j++) {
            course_data course1 = *generatedSchedule[i];
            course_data course2 = *generatedSchedule[j];

            if (typeOfDebug == 1 || typeOfDebug == 3) {
                printf("----------------------------------------------------------------------------------\n");
            }

            if (!validateTimeRange(&course1, &course2, typeOfDebug)) {
                dontContinue = TRUE;
                if (typeOfDebug == 1 || typeOfDebug == 3) {
                    printf("Not possible\n");
                    printf("%s | %s\n", course1.crn, course2.crn);
                }
                break;
            }

            if (isSeminarMatch(&course1, &course2)) {
                seminarCheck = TRUE;
            }
            
            if (typeOfDebug == 1 || typeOfDebug == 3) {
                printf("%s | %s\n", course1.crn, course2.crn);
            }

            numberOfPossibleClasses++;
        }

        if (dontContinue) {
            break;
        }
    }

    if (isValidSchedule(isSeminar, seminarCheck, numberOfPossibleClasses, numberOfAllClasses)) {
        enqueueInt(data.positionQueue, row);
        (*countPossibleSchedules)++;
    }
}

void generateCombination(const course_data courses[], int repeatedCourses[], int row,
                        int countSubjects, int maxCourseOptions, const course_data** temp) {
    int course = 0;
    const course_data* tempCourses[countSubjects][maxCourseOptions];

    for (int row = 0; row < countSubjects; row++) {
        int currentLength = repeatedCourses[row];
        for (int column = 0; column < currentLength; column++) {
            tempCourses[row][column] = &courses[course];
            course++;
        }
    }

    for (int i = countSubjects - 1; i >= 0; i--) {      // Iterate repeatedCourses in reverse
        int currentLength = repeatedCourses[i];         // Copy the length of the repeatedCourses[i] to currentLength
        temp[i] = tempCourses[i][row % currentLength];  // Copy the course from tempCourses[i][row modulo currentLength] to temp[i]
        row = row / currentLength;                      // Divide row by currentLength
    }
}

void combination(const course_data courses[], int numberOfCourses, int repeatedCourses[],
                int countSubjects, const char *titles[], const char *subjects[], int creditHours[]) {
    
    int isSeminar = hasSeminars(courses, numberOfCourses);
    CombinationData data = initializeCombination(repeatedCourses, countSubjects);
    
    int countPossibleSchedules = 0;
    int numberOfAllClasses = countSubjects * (countSubjects - 1) / 2;
    const course_data** temp = malloc(countSubjects * sizeof(const course_data*));

    printf("\n----------------------------------------------------------------------------------\n");
    printf("Calculating all possible schedules                                               |\n");
    clock_t start_time, end_time;
    double elapsed_time;
    start_time = clock();

    for (int row = 0; row < data.maxCombinations; row++) {
        generateCombination(courses, repeatedCourses, row, countSubjects, data.maxCourseOptions, temp);

        validateSchedule(temp, data, &countPossibleSchedules, countSubjects,
        isSeminar, numberOfAllClasses, row);
    }
    end_time = clock();
    elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("All possible schedules have been calculated                                      |\n");
    printf("----------------------------------------------------------------------------------\n");

    course_data **possibleSchedules = malloc(countPossibleSchedules * sizeof(course_data *));
    if (possibleSchedules == NULL) {
        printf("Could not allocate memory for possibleSchedules\n");
        exit(-1);
    }
    
    for (int i = 0; i < countPossibleSchedules; i++) {
        possibleSchedules[i] = malloc(countSubjects * sizeof(course_data));
        if (possibleSchedules[i] == NULL) {
            printf("Could not allocate memory for row %d\n", i);
            exit(-1);
        }
    }

    int row = 0;
    while (!isEmpty(data.positionQueue)) {
        int dequeuedRow = dequeueInt(data.positionQueue);
        if (dequeuedRow != -1) {
            generateCombination(courses, repeatedCourses, dequeuedRow, countSubjects, data.maxCourseOptions, temp);
            for (int i = 0; i < countSubjects; i++) {
                possibleSchedules[row][i] = *temp[i];
            }
            row++;
        } else {
            printf("Error, empty queue position\n");
        }
    }
    free(temp);

    printf("\nElapsed time: %.2f seconds\n", elapsed_time);
    printf("The total number of combinations is: %d\n", data.maxCombinations);
    printf("The total number of valid schedules is: %d\n \n", countPossibleSchedules);

    printf("----------------------------------------------------------------------------------\n");
    printf("Stats\n");
    printf("Size of courses array: %zu KB\n", (sizeof(course_data) * numberOfCourses) / 1000);
    if (typeOfDebug == 2) {
        printf("Size of position queue: %zu KB\n", (countPossibleSchedules * sizeof(int)) / 1000);
    }
    printf("Size of real schedules array: %zu KB\n", countPossibleSchedules * sizeof(course_data) * countSubjects / 1000);
    printf("Total memory used: %zu KB\n", (sizeof(course_data) * numberOfCourses) / 1000 +
                                              (countPossibleSchedules * sizeof(course_data) * countSubjects) / 1000);
    printf("----------------------------------------------------------------------------------\n");

    freeQueue(data.positionQueue);

    printf("\n");
    printSubjectDetails(subjects, titles, repeatedCourses, countSubjects, creditHours);

    printf("----------------------------------------------------------------------------------\n");
    printf("\n");

    processSchedules(countPossibleSchedules, possibleSchedules, countSubjects);
}

void dataProcessor(course_data courses[], int numberOfCourses, int debug) {
    setDebugLevel(debug);
    
    int countSubjects = countDistinctSubjects(courses, numberOfCourses);
    if (countSubjects < 2) {
        printf("\nNo need to calculate anything!\n");
        exit(-1);
    }

    const char *subjects[countSubjects];
    const char *titles[countSubjects];
    int creditHours[countSubjects];

    countSubjects = 0;
    const char *lastTitle = NULL;

    for (int i = 0; i < numberOfCourses; i++) {
        if (lastTitle == NULL || strcmp(courses[i].title, lastTitle) != 0) {
            lastTitle = courses[i].title;
            titles[countSubjects] = lastTitle;
            subjects[countSubjects] = courses[i].subject;
            creditHours[countSubjects] = atoi(courses[i].creditHours);
            countSubjects++;
        }
    }

    int repeatedCourses[countSubjects];

    for (int i = 0; i < countSubjects; i++) {
        int count = countRepeatedCourses(courses, numberOfCourses, titles[i]);
        if (count != -1) {
            repeatedCourses[i] = count;
        } else {
            printf("The title at titles[%d] is NULL\n", i);
            exit(-1);
        }
    }

    combination(courses, numberOfCourses, repeatedCourses, countSubjects, titles, subjects, creditHours);
}