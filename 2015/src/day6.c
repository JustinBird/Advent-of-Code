#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "common.h"

int main() {
    char* data;
    if (get_data("data/day6.txt", &data) != 0) {
        printf("Failed to get data!\n");
        return -1;
    }

    int lights[1000][1000] = {0};
    int x1, y1, x2, y2 = 0;
    char* token = strtok(data, "\n");
    while (token) {
        if (sscanf(token, "toggle %d,%d through %d, %d", &x1, &y1, &x2, &y2) == 4) {
            for (int i = x1; i <= x2; i++) {
                for (int j = y1; j <= y2; j++) {
                    lights[i][j] += 2;
                }
            }
        } else if (sscanf(token, "turn on %d,%d through %d, %d", &x1, &y1, &x2, &y2) == 4) {
            for (int i = x1; i <= x2; i++) {
                for (int j = y1; j <= y2; j++) {
                    lights[i][j]++;
                }
            }
        } else if (sscanf(token, "turn off %d,%d through %d, %d", &x1, &y1, &x2, &y2) == 4) {
            for (int i = x1; i <= x2; i++) {
                for (int j = y1; j <= y2; j++) {
                    if (lights[i][j] > 0){
                        lights[i][j]--;
                    }
                }
            }
        } else {
            printf("Unknown input!\n");
            return 1;
        }
        token = strtok(NULL, "\n");
    }

    int count = 0;
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            count += lights[i][j];
        }
    }

    printf("%d lights turned on!\n", count);
    free(data);

    return 0;
}