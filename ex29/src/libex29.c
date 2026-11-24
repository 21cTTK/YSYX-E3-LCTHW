#include <stdio.h>
#include <ctype.h>
#include "dbg.h"


int print_a_message(const char *msg, size_t length)
{
    printf("A STRING: ");
    fwrite(msg, 1, length, stdout);
    printf("\n");

    return 0;
}


int uppercase(const char *msg, size_t length)
{
    size_t i = 0;

    for(i = 0; i < length; i++) {
        printf("%c", toupper((unsigned char)msg[i]));
    }

    printf("\n");

    return 0;
}

int lowercase(const char *msg, size_t length)
{
    size_t i = 0;

    for(i = 0; i < length; i++) {
        printf("%c", tolower((unsigned char)msg[i]));
    }

    printf("\n");

    return 0;
}

int fail_on_purpose(const char *msg, size_t length)
{
    return 1;
} 
