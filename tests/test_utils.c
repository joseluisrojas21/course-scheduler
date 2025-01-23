#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unity.h"

#include "../include/utils.h"
#include "../include/coursedata.h"

void setUp(void) {
}

void tearDown(void) {
}

// Test cases
void test_1(void) {
    course_data *course1 = malloc(sizeof(course_data));
    if (course1 == NULL) {
        printf("Memory allocation failed for course1\n");
    }

    course1->classStarts_H = strdup("9");
    course1->classStarts_M = strdup("0");
    course1->classEnds_H = strdup("12");
    course1->classEnds_M = strdup("30");

    course_data *course2 = malloc(sizeof(course_data));
    if (course2 == NULL) {
        printf("Memory allocation failed for course2\n");
    }

    course2->classStarts_H = strdup("13");
    course2->classStarts_M = strdup("0");
    course2->classEnds_H = strdup("15");
    course2->classEnds_M = strdup("30");
    TEST_ASSERT_TRUE(checkClassTimeOverlap(course1, course2));
    TEST_ASSERT_TRUE(checkClassTimeOverlap(course2, course1));
    /*
    No overlap
    9:00 - 12:30
    13:00 - 15:30
    */
}

void test_2(void) {
    course_data *course1 = malloc(sizeof(course_data));
    if (course1 == NULL) {
        printf("Memory allocation failed for course1\n");
    }

    course1->classStarts_H = strdup("9");
    course1->classStarts_M = strdup("0");
    course1->classEnds_H = strdup("11");
    course1->classEnds_M = strdup("50");

    course_data *course2 = malloc(sizeof(course_data));
    if (course2 == NULL) {
        printf("Memory allocation failed for course2\n");
    }

    course2->classStarts_H = strdup("10");
    course2->classStarts_M = strdup("30");
    course2->classEnds_H = strdup("12");
    course2->classEnds_M = strdup("20");
    TEST_ASSERT_FALSE(checkClassTimeOverlap(course1, course2));
    TEST_ASSERT_FALSE(checkClassTimeOverlap(course2, course1));
    /*
    Overlap
    9:00 - 11:50
    10:30 - 12:20
    */
}

void test_3(void) {
    course_data *course1 = malloc(sizeof(course_data));
    if (course1 == NULL) {
        printf("Memory allocation failed for course1\n");
    }

    course1->classStarts_H = strdup("9");
    course1->classStarts_M = strdup("0");
    course1->classEnds_H = strdup("11");
    course1->classEnds_M = strdup("50");

    course_data *course2 = malloc(sizeof(course_data));
    if (course2 == NULL) {
        printf("Memory allocation failed for course2\n");
    }

    course2->classStarts_H = strdup("9");
    course2->classStarts_M = strdup("0");
    course2->classEnds_H = strdup("11");
    course2->classEnds_M = strdup("50");

    TEST_ASSERT_FALSE(checkClassTimeOverlap(course1, course2));
    TEST_ASSERT_FALSE(checkClassTimeOverlap(course2, course1));
    /*
    Overlap
    9:00 - 11:50
    9:00 - 11:50
    */
}

void test_4(void) {
    course_data *course1 = malloc(sizeof(course_data));
    if (course1 == NULL) {
        printf("Memory allocation failed for course1\n");
    }

    course1->classStarts_H = strdup("9");
    course1->classStarts_M = strdup("0");
    course1->classEnds_H = strdup("12");
    course1->classEnds_M = strdup("50");

    course_data *course2 = malloc(sizeof(course_data));
    if (course2 == NULL) {
        printf("Memory allocation failed for course2\n");
    }

    course2->classStarts_H = strdup("10");
    course2->classStarts_M = strdup("30");
    course2->classEnds_H = strdup("11");
    course2->classEnds_M = strdup("50");

    TEST_ASSERT_FALSE(checkClassTimeOverlap(course1, course2));
    TEST_ASSERT_FALSE(checkClassTimeOverlap(course2, course1));
    /*
    Overlap
    9:00 - 12:50
    10:30 - 11:50
    */
}

void test_5(void) {
    course_data *course1 = malloc(sizeof(course_data));
    if (course1 == NULL) {
        printf("Memory allocation failed for course1\n");
    }

    course1->classStarts_H = strdup("9");
    course1->classStarts_M = strdup("0");
    course1->classEnds_H = strdup("11");
    course1->classEnds_M = strdup("0");

    course_data *course2 = malloc(sizeof(course_data));
    if (course2 == NULL) {
        printf("Memory allocation failed for course2\n");
    }

    course2->classStarts_H = strdup("10");
    course2->classStarts_M = strdup("30");
    course2->classEnds_H = strdup("12");
    course2->classEnds_M = strdup("0");

    TEST_ASSERT_FALSE(checkClassTimeOverlap(course1, course2));
    TEST_ASSERT_FALSE(checkClassTimeOverlap(course2, course1));
    /*
    Overlap
    9:00 - 11:00
    10:30 - 12:00
    */
}

void test_6(void) {
    course_data *course1 = malloc(sizeof(course_data));
    if (course1 == NULL) {
        printf("Memory allocation failed for course1\n");
    }

    course1->classStarts_H = strdup("9");
    course1->classStarts_M = strdup("0");
    course1->classEnds_H = strdup("10");
    course1->classEnds_M = strdup("0");

    course_data *course2 = malloc(sizeof(course_data));
    if (course2 == NULL) {
        printf("Memory allocation failed for course2\n");
    }

    course2->classStarts_H = strdup("10");
    course2->classStarts_M = strdup("0");
    course2->classEnds_H = strdup("11");
    course2->classEnds_M = strdup("0");

    TEST_ASSERT_FALSE(checkClassTimeOverlap(course1, course2));
    TEST_ASSERT_FALSE(checkClassTimeOverlap(course2, course1));
    /*
    Overlap
    9:00 - 10:00
    10:00 - 11:00
    */
}

void test_7(void) {
    course_data *course1 = malloc(sizeof(course_data));
    if (course1 == NULL) {
        printf("Memory allocation failed for course1\n");
    }

    course1->classStarts_H = strdup("12");
    course1->classStarts_M = strdup("0");
    course1->classEnds_H = strdup("13");
    course1->classEnds_M = strdup("20");

    course_data *course2 = malloc(sizeof(course_data));
    if (course2 == NULL) {
        printf("Memory allocation failed for course2\n");
    }

    course2->classStarts_H = strdup("9");
    course2->classStarts_M = strdup("0");
    course2->classEnds_H = strdup("10");
    course2->classEnds_M = strdup("20");

    TEST_ASSERT_TRUE(checkClassTimeOverlap(course1, course2));
    TEST_ASSERT_TRUE(checkClassTimeOverlap(course2, course1));
    /*
    No Overlap
    12:00 - 13:20
    9:00 - 10:20
    */
}

void test_8(void) {
    course_data *course1 = malloc(sizeof(course_data));
    if (course1 == NULL) {
        printf("Memory allocation failed for course1\n");
    }

    course1->classStarts_H = strdup("12");
    course1->classStarts_M = strdup("0");
    course1->classEnds_H = strdup("13");
    course1->classEnds_M = strdup("20");

    course_data *course2 = malloc(sizeof(course_data));
    if (course2 == NULL) {
        printf("Memory allocation failed for course2\n");
    }

    course2->classStarts_H = strdup("13");
    course2->classStarts_M = strdup("30");
    course2->classEnds_H = strdup("14");
    course2->classEnds_M = strdup("20");

    TEST_ASSERT_TRUE(checkClassTimeOverlap(course1, course2));
    TEST_ASSERT_TRUE(checkClassTimeOverlap(course2, course1));
    /*
    No Overlap
    12:00 - 13:20
    13:30 - 14:20
    */
}

void test_9(void) {
    course_data *course1 = malloc(sizeof(course_data));
    if (course1 == NULL) {
        printf("Memory allocation failed for course1\n");
    }

    course1->classStarts_H = strdup("12");
    course1->classStarts_M = strdup("0");
    course1->classEnds_H = strdup("13");
    course1->classEnds_M = strdup("20");

    course_data *course2 = malloc(sizeof(course_data));
    if (course2 == NULL) {
        printf("Memory allocation failed for course2\n");
    }

    course2->classStarts_H = strdup("14");
    course2->classStarts_M = strdup("30");
    course2->classEnds_H = strdup("16");
    course2->classEnds_M = strdup("20");

    TEST_ASSERT_TRUE(checkClassTimeOverlap(course1, course2));
    TEST_ASSERT_TRUE(checkClassTimeOverlap(course2, course1));
    /*
    No Overlap
    12:00 - 13:20
    14:30 - 16:20
    */
}

void test_10(void) {
    course_data *course1 = malloc(sizeof(course_data));
    if (course1 == NULL) {
        printf("Memory allocation failed for course1\n");
    }

    course1->classStarts_H = strdup("9");
    course1->classStarts_M = strdup("0");
    course1->classEnds_H = strdup("10");
    course1->classEnds_M = strdup("20");

    course_data *course2 = malloc(sizeof(course_data));
    if (course2 == NULL) {
        printf("Memory allocation failed for course2\n");
    }

    course2->classStarts_H = strdup("13");
    course2->classStarts_M = strdup("30");
    course2->classEnds_H = strdup("14");
    course2->classEnds_M = strdup("20");

    TEST_ASSERT_TRUE(checkClassTimeOverlap(course1, course2));
    TEST_ASSERT_TRUE(checkClassTimeOverlap(course2, course1));
    /*
    No Overlap
    9 :00 - 10:20
    13:30 - 14:20
    */
}

void test_11(void) {
    course_data *course1 = malloc(sizeof(course_data));
    if (course1 == NULL) {
        printf("Memory allocation failed for course1\n");
    }

    course1->classStarts_H = strdup("9");
    course1->classStarts_M = strdup("0");
    course1->classEnds_H = strdup("10");
    course1->classEnds_M = strdup("20");

    course_data *course2 = malloc(sizeof(course_data));
    if (course2 == NULL) {
        printf("Memory allocation failed for course2\n");
    }

    course2->classStarts_H = strdup("14");
    course2->classStarts_M = strdup("30");
    course2->classEnds_H = strdup("16");
    course2->classEnds_M = strdup("20");

    TEST_ASSERT_TRUE(checkClassTimeOverlap(course1, course2));
    TEST_ASSERT_TRUE(checkClassTimeOverlap(course2, course1));
    /*
    No Overlap
    9 :00 - 10:20
    14:30 - 16:20
    */
}

void test_12(void) {
    course_data *course1 = malloc(sizeof(course_data));
    if (course1 == NULL) {
        printf("Memory allocation failed for course1\n");
    }

    course1->classStarts_H = strdup("13");
    course1->classStarts_M = strdup("30");
    course1->classEnds_H = strdup("14");
    course1->classEnds_M = strdup("20");

    course_data *course2 = malloc(sizeof(course_data));
    if (course2 == NULL) {
        printf("Memory allocation failed for course2\n");
    }

    course2->classStarts_H = strdup("14");
    course2->classStarts_M = strdup("30");
    course2->classEnds_H = strdup("16");
    course2->classEnds_M = strdup("20");

    TEST_ASSERT_TRUE(checkClassTimeOverlap(course1, course2));
    TEST_ASSERT_TRUE(checkClassTimeOverlap(course2, course1));
    /*
    No Overlap
    13:30 - 14:20
    14:30 - 16:20
    */
}

void test_13(void) {
    course_data *course1 = malloc(sizeof(course_data));
    if (course1 == NULL) {
        printf("Memory allocation failed for course1\n");
    }

    course1->classStarts_H = strdup("13");
    course1->classStarts_M = strdup("30");
    course1->classEnds_H = strdup("14");
    course1->classEnds_M = strdup("50");

    course_data *course2 = malloc(sizeof(course_data));
    if (course2 == NULL) {
        printf("Memory allocation failed for course2\n");
    }

    course2->classStarts_H = strdup("9");
    course2->classStarts_M = strdup("0");
    course2->classEnds_H = strdup("10");
    course2->classEnds_M = strdup("20");

    TEST_ASSERT_TRUE(checkClassTimeOverlap(course1, course2));
    TEST_ASSERT_TRUE(checkClassTimeOverlap(course2, course1));
    /*
    No Overlap
    13:30 - 14:50
    9 :00 - 10:20
    */
}

// Testing
void test_14(void) {
    course_data *course1 = malloc(sizeof(course_data));
    if (course1 == NULL) {
        printf("Memory allocation failed for course1\n");
    }

    course1->days = strdup("M W");
    course1->classStarts_H = strdup("12");
    course1->classStarts_M = strdup("0");
    course1->classEnds_H = strdup("13");
    course1->classEnds_M = strdup("20");

    course_data *course2 = malloc(sizeof(course_data));
    if (course2 == NULL) {
        printf("Memory allocation failed for course2\n");
    }

    course2->days = strdup("M W");
    course2->classStarts_H = strdup("9");
    course2->classStarts_M = strdup("0");
    course2->classEnds_H = strdup("10");
    course2->classEnds_M = strdup("20");

    TEST_ASSERT_TRUE(validateTimeRange(course1, course2, 0));
    TEST_ASSERT_TRUE(validateTimeRange(course2, course1, 0));
}

void test_15(void) {
    course_data *course1 = malloc(sizeof(course_data));
    if (course1 == NULL) {
        printf("Memory allocation failed for course1\n");
    }

    course1->days = strdup("T R");
    course1->classStarts_H = strdup("12");
    course1->classStarts_M = strdup("0");
    course1->classEnds_H = strdup("13");
    course1->classEnds_M = strdup("20");

    course_data *course2 = malloc(sizeof(course_data));
    if (course2 == NULL) {
        printf("Memory allocation failed for course2\n");
    }

    course2->days = strdup("M W");
    course2->classStarts_H = strdup("9");
    course2->classStarts_M = strdup("0");
    course2->classEnds_H = strdup("10");
    course2->classEnds_M = strdup("20");

    TEST_ASSERT_TRUE(validateTimeRange(course1, course2, 0));
    TEST_ASSERT_TRUE(validateTimeRange(course2, course1, 0));
}

void test_16(void) {
    course_data *course1 = malloc(sizeof(course_data));
    if (course1 == NULL) {
        printf("Memory allocation failed for course1\n");
    }

    course1->days = strdup("W");
    course1->classStarts_H = strdup("12");
    course1->classStarts_M = strdup("0");
    course1->classEnds_H = strdup("13");
    course1->classEnds_M = strdup("20");

    course_data *course2 = malloc(sizeof(course_data));
    if (course2 == NULL) {
        printf("Memory allocation failed for course2\n");
    }

    course2->days = strdup("M W");
    course2->classStarts_H = strdup("11");
    course2->classStarts_M = strdup("0");
    course2->classEnds_H = strdup("12");
    course2->classEnds_M = strdup("50");

    TEST_ASSERT_FALSE(validateTimeRange(course1, course2, 0));
    TEST_ASSERT_FALSE(validateTimeRange(course2, course1, 0));
}

void test_find_inside_range(void) {
    int result = inRange(10, 20, 15);
    TEST_ASSERT_TRUE(result);
}

void test_find_inside_range_inverse(void) {
    int result = inRange(20, 10, 15);
    TEST_ASSERT_TRUE(result);
}

void test_find_above_range(void) {
    int result = inRange(10, 20, 25);
    TEST_ASSERT_FALSE(result);
}

void test_find_below_range(void) {
    int result = inRange(20, 10, 5);
    TEST_ASSERT_FALSE(result);
}

void test_boundary_low(void) {
    int result = inRange(10, 20, 10);
    TEST_ASSERT_TRUE(result);
}

void test_boundary_high(void) {
    int result = inRange(10, 20, 20);
    TEST_ASSERT_TRUE(result);
}

void test_single_point(void) {
    int result = inRange(10, 10, 10);
    TEST_ASSERT_TRUE(result);
}

void test_single_point_outside(void) {
    int result = inRange(10, 10, 5);
    TEST_ASSERT_FALSE(result);
}

void test_negative_range(void) {
    int result = inRange(-20, -10, -15);
    TEST_ASSERT_TRUE(result);
}

void test_negative_outside(void) {
    int result = inRange(-20, -10, -5);
    TEST_ASSERT_FALSE(result);
}

void test_upperCase_normalString(void) {
    char input[] = "hello world";
    char expected[] = "HELLO WORLD";
    TEST_ASSERT_EQUAL_STRING(expected, upperCase(input));
}

void test_upperCase_emptyString(void) {
    char input[] = "";
    char expected[] = "";
    TEST_ASSERT_EQUAL_STRING(expected, upperCase(input));
}

void test_upperCase_alreadyUppercase(void) {
    char input[] = "HELLO WORLD";
    char expected[] = "HELLO WORLD";
    TEST_ASSERT_EQUAL_STRING(expected, upperCase(input));
}

void test_upperCase_specialCharacters(void) {
    char input[] = "hello!@#";
    char expected[] = "HELLO!@#";
    TEST_ASSERT_EQUAL_STRING(expected, upperCase(input));
}

void test_getMaxLengths(void) {
    course_data courses[4];
    courses[0].days = "M W";
    courses[0].subject = "MATH";
    courses[0].title = "Mathematics 101";

    courses[1].days = "M";
    courses[1].subject = "CS";
    courses[1].title = "Data Structures";

    courses[2].days = "T R";
    courses[2].subject = "CHEM";
    courses[2].title = "General Chemistry";

    courses[3].days = "W";
    courses[3].subject = "PHYS";
    courses[3].title = "Physics Fundamentals";

    int maxLengthOfDays = 0;
    int maxLengthOfSubject = 0;
    int maxLengthOfTitle = 0;
    int countSubjects = 4;

    getMaxLengths(courses, countSubjects, &maxLengthOfDays, &maxLengthOfSubject, &maxLengthOfTitle);

    TEST_ASSERT_EQUAL(3, maxLengthOfDays);     // "M W" has 3 characters
    TEST_ASSERT_EQUAL(4, maxLengthOfSubject);  // "MATH" has 4 characters
    TEST_ASSERT_EQUAL(20, maxLengthOfTitle);   // "Physics Fundamentals" has 20 characters
}

void test_empty_courses(void) {
    course_data courses[] = {};

    int maxLengthOfDays = 0;
    int maxLengthOfSubject = 0;
    int maxLengthOfTitle = 0;
    int countSubjects = 0;

    getMaxLengths(courses, countSubjects, &maxLengthOfDays, &maxLengthOfSubject, &maxLengthOfTitle);

    TEST_ASSERT_EQUAL(0, maxLengthOfDays);
    TEST_ASSERT_EQUAL(0, maxLengthOfSubject);
    TEST_ASSERT_EQUAL(0, maxLengthOfTitle);
}

void test_countNumberOfSeminars_valid_input(void) {
    const char *seminars = "19820 19821 19822 19827";
    int result = countNumberOfSeminars(seminars);
    TEST_ASSERT_EQUAL(4, result);
}

void test_countNumberOfSeminars_empty_input(void) {
    const char *seminars = "";
    int result = countNumberOfSeminars(seminars);
    TEST_ASSERT_EQUAL(0, result);
}

void test_countNumberOfSeminars_single_seminar(void) {
    const char *seminars = "19820";
    int result = countNumberOfSeminars(seminars);
    TEST_ASSERT_EQUAL(1, result);
}

void test_countNumberOfSeminars_leading_trailing_spaces(void) {
    const char *seminars = "   19820 19821 19827   ";
    int result = countNumberOfSeminars(seminars);
    TEST_ASSERT_EQUAL(3, result);
}

void test_countNumberOfSeminars_multiple_spaces_between_words(void) {
    const char *seminars = "19820    19821     19827";
    int result = countNumberOfSeminars(seminars);
    TEST_ASSERT_EQUAL(3, result);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_1);
    RUN_TEST(test_2);
    RUN_TEST(test_3);
    RUN_TEST(test_4);
    RUN_TEST(test_5);
    RUN_TEST(test_6);
    RUN_TEST(test_7);
    RUN_TEST(test_8);
    RUN_TEST(test_9);
    RUN_TEST(test_10);
    RUN_TEST(test_11);
    RUN_TEST(test_12);
    RUN_TEST(test_13);
    RUN_TEST(test_14);
    RUN_TEST(test_15);
    RUN_TEST(test_16);


    RUN_TEST(test_find_inside_range);
    RUN_TEST(test_find_inside_range_inverse);
    RUN_TEST(test_find_above_range);
    RUN_TEST(test_find_below_range);
    RUN_TEST(test_boundary_low);
    RUN_TEST(test_boundary_high);
    RUN_TEST(test_single_point);
    RUN_TEST(test_single_point_outside);
    RUN_TEST(test_negative_range);
    RUN_TEST(test_negative_outside);

    RUN_TEST(test_upperCase_normalString);
    RUN_TEST(test_upperCase_emptyString);
    RUN_TEST(test_upperCase_alreadyUppercase);
    RUN_TEST(test_upperCase_specialCharacters);
    RUN_TEST(test_getMaxLengths);
    RUN_TEST(test_empty_courses);

    RUN_TEST(test_countNumberOfSeminars_valid_input);
    RUN_TEST(test_countNumberOfSeminars_empty_input);
    RUN_TEST(test_countNumberOfSeminars_single_seminar);
    RUN_TEST(test_countNumberOfSeminars_leading_trailing_spaces);
    RUN_TEST(test_countNumberOfSeminars_multiple_spaces_between_words);

    return UNITY_END();
}
