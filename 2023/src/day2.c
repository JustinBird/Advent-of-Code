#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>

#include "common.h"

void skip_to_colon(char** line) {
    *line += 1;
    while (**line != ':') {
        *line += 1;
    }
}

void skip_to_num(char** line) {
    while (**line) {
        if (**line >= '0' && **line <= '9') {
            break;
        }
        *line += 1;
    }
}

void skip_to_space(char** line) {
    while (**line) {
        if (**line == ' ') {
            break;
        }
        *line += 1;
    }
}


bool is_round_over(char* line) {
    while (*line) {
        if (*line == ',') {
            return false;
        } else if (*line == ';') {
            return true;
        }

        line += 1;
    }

    return true;
}

int is_possible(char* line, int* power) {
    int game;
    if (sscanf(line, "Game %d:", &game) != 1) {
        printf("Failed to fine game ID!\n");
        exit(0);
    }
    printf("Game %d\n", game);
    skip_to_colon(&line);
    skip_to_num(&line);
    int val;
    int r = 0, g = 0, b = 0;
    int maxR = 0, maxG = 0, maxB = 0;
    char color[10];
    while (*line) {
        if (sscanf(line, "%d %s", &val, color) == 2) {
            if (strncmp(color, "red", strlen("red")) == 0) {
                r += val;
            } else if (strncmp(color, "green", strlen("green")) == 0) {
                g += val;
            } else if (strncmp(color, "blue", strlen("blue")) == 0) {
                b += val;
            } else {
                printf("Failed to match color: %s!\n", color);
                exit(1);
            }
        } else {
            printf("Failed to read input!\n");
            exit(1);
        }

        if (r > 12 || g > 13 || b > 14) {
            game = 0;
        }

        if (is_round_over(line)) {
            if (r > maxR) {
                maxR = r;
            }

            if (g > maxG) {
                maxG = g;
            }

            if (b > maxB) {
                maxB = b;
            }

            printf("%d red %d green %d blue\n", r, g, b);
            r = 0, g = 0, b = 0;
        }
        skip_to_space(&line);
        skip_to_num(&line);
    }

    *power += maxR * maxG * maxB;
    return game;
}

int main() {
    char* data;
    if (get_data("data/day2.txt", &data) != 0) {
        printf("Failed to get data!\n");
        return -1;
    }

    int sum = 0;
    int powerSum = 0;
    char* token = strtok(data, "\n");
    while (token) {
        sum += is_possible(token, &powerSum);
        token = strtok(NULL, "\n");
    }

    printf("%d total!\n", sum);
    printf("%d power sum!\n", powerSum);
    free(data);

    return 0;
}