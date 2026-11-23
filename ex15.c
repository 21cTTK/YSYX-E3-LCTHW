#include <stdio.h>

void print_arrays(char *names[], int ages[], int count)
{
    int i = 0;
    while (i < count) {
        printf("%s has %d years alive.\n", names[i], ages[i]);
        i++;
    }
}

void print_offsets(char **cur_name, int *cur_age, int count)
{
    int i = 0;
    while (i < count) {
        printf("%s is %d years old.\n", *(cur_name + i), *(cur_age + i));
        i++;
    }
}

void print_indexed(char **cur_name, int *cur_age, int count)
{
    int i = 0;
    while (i < count) {
        printf("%s is %d years old again.\n", cur_name[i], cur_age[i]);
        i++;
    }
}

void print_walk(char **cur_name, int *cur_age, int *end)
{
    while (cur_age != end) {
        printf("%s lived %d years so far.\n", *cur_name, *cur_age);
        cur_name++;
        cur_age++;
    }
}

int main(int argc, char *argv[])
{
    // create two arrays we care about
    int ages[] = { 23, 43, 12, 89, 2 };
    char *names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };

    // safely get the size of ages
    int count = sizeof(ages) / sizeof(int);

    print_arrays(names, ages, count);
    printf("---\n");

    print_offsets(names, ages, count);
    printf("---\n");

    print_indexed(names, ages, count);
    printf("---\n");

    print_walk(names, ages, ages + count);

    for (int i = 0; i < count; i++) {
        printf("%s: %p %p\n", names[i], (void *)(names + i), (void *)(ages + i));
    }

    for (char **arg = argv + 1; *arg; arg++) {
        printf("arg: %s\n", *arg);
    }

    return 0;
}
