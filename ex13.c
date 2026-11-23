#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;

    // let's make our own array of strings
    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas", NULL
    };

    int num_states = 5;

    if (argc > 1) {
        char *arg = argv[1];
        argv[1] = states[0];
        states[0] = arg;
    }

    int args_printed = 0;
    // go through each string in argv
    // why am I skipping argv[0]?
    for (i = 1, args_printed = 0; i < argc; i++, args_printed++) {
        printf("arg %d: %s\n", i, argv[i]);
    }
    printf("%d arguments\n", args_printed);

    for (i = 0; i < num_states; i++) {
        printf("state %d: %s\n", i, states[i] ? states[i] : "(null)");
    }

    return 0;
}
