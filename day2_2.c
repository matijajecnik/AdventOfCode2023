#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calculatePower(int redCount, int greenCount, int blueCount) {
    return redCount * greenCount * blueCount;
}

void findMinimumSet(char *game, int *minRed, int *minGreen, int *minBlue) {
    char *endRound;
    char *round = strtok_r(game, ";", &endRound);
    while (round != NULL) {
        char *endToken;
        char *token = strtok_r(round, ",", &endToken);
        while (token != NULL) {
            int quantity;
            char color[10];
            sscanf(token, "%d %s", &quantity, color);
            if (color[0] == 'r' && quantity > *minRed) {
                *minRed = quantity;
            } else if (color[0] == 'g' && quantity > *minGreen) {
                *minGreen = quantity;
            } else if (color[0] == 'b' && quantity > *minBlue) {
                *minBlue = quantity;
            }
            token = strtok_r(NULL, ",", &endToken);
        }
        round = strtok_r(NULL, ";", &endRound);
    }
}

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

    int sumOfPowers = 0;
    char line[256];

    while (fgets(line, sizeof(line), file) != NULL) {
        char *strPos = strchr(line, ':');
        if (strPos != NULL) {
            strPos++;
            int minRed = 0, minGreen = 0, minBlue = 0;
            findMinimumSet(strPos, &minRed, &minGreen, &minBlue);
            sumOfPowers += calculatePower(minRed, minGreen, minBlue);
        }
    }

    fclose(file);

    printf("%d\n", sumOfPowers);

    return 0;
}
