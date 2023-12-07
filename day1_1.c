#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <inputFile>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", argv[1]);
        return 1;
    }

    int sum = 0;

    char line[256];

    while (fgets(line, sizeof(line), file) != NULL) {
        int firstDigit, lastDigit;

        for (int i = 0; i < strlen(line); i++) {
            if (isdigit(line[i])) {
                firstDigit = line[i] - '0';
                break;
            }
        }

        for (int i = strlen(line) - 1; i >= 0; i--) {
            if (isdigit(line[i])) {
                lastDigit = line[i] - '0';
                break;
            }
        }

        int calibrationValue = firstDigit * 10 + lastDigit;

        sum += calibrationValue;
    }

    fclose(file);

    printf("%d\n", sum);

    return 0;
}
