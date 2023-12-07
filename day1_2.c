#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int getDigitStart(char *line, int i) {
    switch (line[i]) {
        case 'o':
            if (line[i + 1] == 'n' && line[i + 2] == 'e') {
                return 1;
            }
        case 't':
            if (line[i + 1] == 'w' && line[i + 2] == 'o') {
                return 2;
            }
            if (line[i + 1] == 'h' && line[i + 2] == 'r' && line[i + 3] == 'e' && line[i + 4] == 'e') {
                return 3;
            }
        case 'f':
            if (line[i + 1] == 'o' && line[i + 2] == 'u' && line[i + 3] == 'r') {
                return 4;
            }
            if (line[i + 1] == 'i' && line[i + 2] == 'v' && line[i + 3] == 'e') {
                return 5;
            }
        case 's':
            if (line[i + 1] == 'i' && line[i + 2] == 'x') {
                return 6;
            }
            if (line[i + 1] == 'e' && line[i + 2] == 'v' && line[i + 3] == 'e' && line[i + 4] == 'n') {
                return 7;
            }
        case 'e':
            if (line[i + 1] == 'i' && line[i + 2] == 'g' && line[i + 3] == 'h' && line[i + 4] == 't') {
                return 8;
            }
        case 'n':
            if (line[i + 1] == 'i' && line[i + 2] == 'n' && line[i + 3] == 'e') {
                return 9;
            }
        default:
            return 0;
    }
}

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <inputFile>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", argv[1]);
        return 1;
    }

    char line[256];
    int sum = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        int firstDigit, lastDigit;

        for (int i = 0; i < strlen(line); i++) {
            if (isdigit(line[i])) {
                firstDigit = line[i] - '0';
                break;
            } else {
                firstDigit = getDigitStart(line, i);
                if (firstDigit != 0) {
                    break;
                }
            }
        }

        for (int i = strlen(line) - 1; i >= 0; i--) {
            if (isdigit(line[i])) {
                lastDigit = line[i] - '0';
                break;
            } else {
                lastDigit = getDigitStart(line, i);
                if (lastDigit != 0) {
                    break;
                }
            }
        }

        int calibrationValue = firstDigit * 10 + lastDigit;
        sum += calibrationValue;
    }
    fclose(file);
    printf("%d\n", sum);

    return 0;
}
