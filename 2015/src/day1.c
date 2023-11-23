#include <stdio.h>
#include <string.h>

#include "common.h"

int main() {
    char* data;
    if (get_data("data/day1.txt", &data) != 0) {
        printf("Failed to get data!\n");
        return -1;
    }

    int floor = 0;
    int basement = -1;
    for (int i = 0; i < strlen(data); i++) {
        if (floor < 0 && basement == -1) {
            basement = i;
        }

        if (data[i] == '(') {
            floor += 1;
        } else if (data[i] == ')') {
            floor -= 1;
        }
    }

    printf("Ending floor: %d\n", floor);
    printf("First basement at: %d\n", basement);
    return 0;
}