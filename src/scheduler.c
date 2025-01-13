#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/courses.h"

#define TRUE 1

int main(int argc, char *argv[]) {
    int debug = -1;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0) {
            if (i + 1 < argc) {
                debug = atoi(argv[i + 1]);
                break;
            } else {
                printf("Error: -d requires an option\n");
                printf("1: Debug course combination generation\n");
                printf("2: Debug position queue size\n");
                printf("3: Debug time and date comparison\n");
                exit(0);
            }
        } else {
            printf("Use -d debugLevel or just -d to view options\n");
            exit(0);
        }
    }

    printf("----------------------------------------------------------------------------------\n");
    printf("Ensure the file is formatted as follows:\n\n");
    printf("CRN,Course,Section Number,Credit Hours,Title,Days,Time,Workshop,Instructor Name,Building\n");
    printf("11889,CS,2302,3,Data Structures,M W,12:00 - 13:20,,Instructor Name,CCSB G.0208\n");
    printf("----------------------------------------------------------------------------------\n");
    printf("\nEnter the name of the CSV file. Do not include spaces in the filename\nand do not add .csv at the end.\n\n");
    char filename[105];
    scanf("%99s", filename);
    strcat(filename, ".csv");

    printf("\nType Y to continue or N to exit\n\n");

    char option[2];
    scanf("%s", option);
    while (TRUE) {
        if (!strcmp(option,"Y") || !strcmp(option,"y")) {
            loadData(debug, filename);
        } else if (!strcmp(option,"N") || !strcmp(option,"n")) {
            exit(0);
        } else {
            printf("Type Y or N\n\n");
            scanf("%s", option);
        }
    }
    return 0;
}