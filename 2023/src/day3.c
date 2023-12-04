#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>

#include "common.h"

bool is_num(char c) {
    return c >= '0' && c <= '9';
}

bool is_symbol(char c) {
    return (c != '.' && c != '\n' && (c < '0' || c > '9'));
}

bool in_bounds(int x, int y, int width, int height) {
    return x >= 0 && x < width && y >= 0 && y < height;
}

bool is_part_number(char lines[][200], int width, int height, int startX, int startY) {
    for (int x = startX - 1; x <= startX + 1; x++) {
        for (int y = startY - 1; y <= startY + 1; y++) {
            if (in_bounds(x, y, width, height)) {
                if (is_symbol(lines[y][x])) {
                    return true;
                }
            }
        }
    }

    return false;
}

int gear_ratio(char lines[][200], int width, int height, int startX, int startY) {

    int gear_ratio = 1;
    int adjacents = 0;
    for (int y = startY - 1; y <= startY + 1; y++) {
        int top_startX = startX + 1;
        int num = 0, multiplier = 1;
        while (in_bounds(top_startX, y, width, height) && is_num(lines[y][top_startX])) {
            top_startX += 1;
        }

        while (top_startX >= startX || is_num(lines[y][top_startX])) {
            if (is_num(lines[y][top_startX])) {
                int digit = lines[y][top_startX] - '0';
                num += digit * multiplier;
                multiplier *= 10;
            } else {
                if (num != 0) {
                    adjacents += 1;
                    gear_ratio *= num;
                }
                num = 0, multiplier = 1;
            }

            top_startX -= 1;
        }

        if (num != 0) {
            adjacents += 1;
            gear_ratio *= num;
        }
    }

    if (gear_ratio == 1 || adjacents != 2) {
        return 0;
    } else {
        return gear_ratio;
    }
}

int main() {
    char* data;
    if (get_data("data/day3.txt", &data) != 0) {
        printf("Failed to get data!\n");
        return -1;
    }

    char lines[200][200];
    char* token = strtok(data, "\n");
    int width = strlen(token) - 1;
    int height = 0;
    while (token) {
        strcpy(lines[height++], token);
        token = strtok(NULL, "\n");
    }

    int sum = 0;
    int total_gear_ratio = 0;
    int count = 0;
    int multiplier = 1;
    bool part_num = false;
    for (int i = height - 1; i >= 0; i--) {
        for(int j = width - 1; j >= 0; j--) {
            if (lines[i][j] >= '0' && lines[i][j] <= '9') {
                int digit = lines[i][j] - '0';
                count += digit * multiplier;
                multiplier *= 10;

                if (is_part_number(lines, width, height, j, i)) {
                    part_num = true;
                }
            } else if (part_num) {
                sum += count;
                count = 0, multiplier = 1, part_num = false;
            } else {
                count = 0, multiplier = 1, part_num = false;
            }

            if (lines[i][j] == '*') {
                total_gear_ratio += gear_ratio(lines, width, height, j, i);
            }
        }

        if (part_num) {
            sum += count;
        }
        count = 0, multiplier = 1, part_num = false;
    }

    if (part_num) {
        sum += count;
    }

    printf("sum: %d\n", sum);
    printf("total_gear_ratio: %d\n", total_gear_ratio);
    free(data);

    return 0;
}