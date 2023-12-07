#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isPossible(char *game) {
    int redCount = 12, greenCount = 13, blueCount = 14;

    char *endRound;
    char *round = strtok_r(game, ";", &endRound);
    int quantity;
    char color[10];
    while (round != NULL) {
        char *endToken;
        char *token = strtok_r(round, ",", &endToken);
        while (token != NULL) {
            sscanf(token, "%d %s", &quantity, color);
            if (color[0] == 'r') {
                if (quantity > redCount) return 0;
            } else if (color[0] == 'g') {
                if (quantity > greenCount) return 0;
            } else if (color[0] == 'b') {
                if (quantity > blueCount) return 0;
            }
            token = strtok_r(NULL, ",", &endToken);
        }
        round = strtok_r(NULL, ";", &endRound);
    }

    return 1;
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

    int sum = 0;
    char line[256];

    while (fgets(line, sizeof(line), file) != NULL) {
        char *strPos = strchr(line, ':');
        if (strPos != NULL) {
            strPos++;
            if (isPossible(strPos)) {
                int gameID;
                sscanf(line, "Game %d", &gameID);
                sum += gameID;
            }
        }
    }

    fclose(file);

    printf("%d\n", sum);

    return 0;
}
