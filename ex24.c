#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"

#define MAX_DATA 100

typedef enum EyeColor {
    BLUE_EYES, GREEN_EYES, BROWN_EYES,
    BLACK_EYES, OTHER_EYES
} EyeColor;

const char *EYE_COLOR_NAMES[] = {
    "Blue", "Green", "Brown", "Black", "Other"
};

typedef struct Person {
    int age;
    char first_name[MAX_DATA];
    char last_name[MAX_DATA];
    EyeColor eyes;
    float income;
} Person;

int read_line(char *text, size_t size)
{
    if (size == 0)
        return -1;

    size_t length = 0;
    int full = 0;
    char ch;
    int rc;

    while ((rc = scanf("%c", &ch)) == 1 && ch != '\n') {
        if (length + 1 < size) {
            text[length++] = ch;
        } else {
            full = 1;
        }
    }
    text[length] = '\0';

    if (full || ferror(stdin) || (rc != 1 && length == 0))
        return -1;

    while (length && isspace((unsigned char)text[length - 1]))
        text[--length] = '\0';

    size_t start = 0;
    while (isspace((unsigned char)text[start]))
        start++;
    memmove(text, text + start, length - start + 1);
    return 0;
}

int read_int(int *result)
{
    char text[MAX_DATA];
    if (read_line(text, sizeof(text)) != 0)
        return -1;

    char *end;
    errno = 0;
    long number = strtol(text, &end, 10);
    if (errno || end == text || *end || number < INT_MIN || number > INT_MAX)
        return -1;

    *result = number;
    return 0;
}

int main(int argc, char *argv[])
{
    Person you = {.age = 0 };
    int i = 0;
    char income[MAX_DATA];

    printf("What's your First Name? ");
    check(read_line(you.first_name, sizeof(you.first_name)) == 0,
            "Failed to read first name.");

    printf("What's your Last Name? ");
    check(read_line(you.last_name, sizeof(you.last_name)) == 0,
            "Failed to read last name.");

    printf("How old are you? ");
    check(read_int(&you.age) == 0, "You have to enter a number.");

    printf("What color are your eyes:\n");
    for (i = 0; i <= OTHER_EYES; i++) {
        printf("%d) %s\n", i + 1, EYE_COLOR_NAMES[i]);
    }
    printf("> ");

    int eyes = -1;
    check(read_int(&eyes) == 0, "You have to enter a number.");

    check(eyes >= 1 && eyes <= OTHER_EYES + 1, "Do it right, that's not an option.");
    you.eyes = eyes - 1;

    printf("How much do you make an hour? ");
    check(read_line(income, sizeof(income)) == 0, "Enter a floating point number.");
    char *end;
    errno = 0;
    you.income = strtof(income, &end);
    check(!errno && end != income && !*end, "Enter a floating point number.");

    printf("----- RESULTS -----\n");

    printf("First Name: %s\n", you.first_name);
    printf("Last Name: %s\n", you.last_name);
    printf("Age: %d\n", you.age);
    printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
    printf("Income: %f\n", you.income);

    return 0;
error:

    return -1;
}
