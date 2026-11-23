#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("ERROR: You need at least one argument.\n");
        // this is how you abort a program
        return 1;
    }

    for (int arg = 1; arg < argc; arg++) {
        int i = 0;
        char letter;
        for (i = 0, letter = argv[arg][i]; letter != '\0';
                i++, letter = argv[arg][i]) {
            if (letter >= 'A' && letter <= 'Z') {
                letter += 'a' - 'A';
            }

            if (letter == 'a') {
                printf("%d: 'A'\n", i);
            } else if (letter == 'e') {
                printf("%d: 'E'\n", i);
            } else if (letter == 'i') {
                printf("%d: 'I'\n", i);
            } else if (letter == 'o') {
                printf("%d: 'O'\n", i);
            } else if (letter == 'u') {
                printf("%d: 'U'\n", i);
            } else if (letter == 'y') {
                if (i > 2) {
                    printf("%d: 'Y'\n", i);
                }
            } else {
                printf("%d: %c is not a vowel\n", i, argv[arg][i]);
            }
        }
    }

    return 0;
}
