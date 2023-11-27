#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "common.h"

struct House {
    int x;
    int y;
};

int check_for_house(struct House* houses, int num_houses, struct House potential_house) {
    for (int i = 0; i < num_houses; i++) {
        if (houses[i].x == potential_house.x && houses[i].y == potential_house.y) {
            return 0;
        }
    }

    return 1;
}

void move_house(struct House* house, char direction) {
    switch(direction) {
    case '>':
        house->x += 1;
        break;
    case 'v':
        house->y += 1;
        break;
    case '<':
        house->x -= 1;
        break;
    case '^':
        house->y -= 1;
        break;
    }
}

int main() {
    char* data;
    if (get_data("data/day3.txt", &data) != 0) {
        printf("Failed to get data!\n");
        return -1;
    }

    int num_houses = 0;
    int house_capacity = 10000;
    struct House* houses = malloc(sizeof(struct House) * house_capacity);
    if (houses == NULL) {
        printf("Failed to allocate memory!\n");
        return -1;
    }

    struct House potential_house = { 0, 0 };
    size_t length = strlen(data);
    for (size_t i = 0; i < length; i++) {
        if (check_for_house(houses, num_houses, potential_house)) {
            houses[num_houses] = potential_house;
            num_houses++;
        }

        move_house(&potential_house, data[i]);
    }
    printf("%d houses were visited!\n", num_houses);

    // part 2
    num_houses = 0;
    struct House santa_house = { 0, 0 };
    struct House robo_house = { 0, 0 };
    size_t i = 0;
    while (i < length) {
        if (check_for_house(houses, num_houses, santa_house)) {
            houses[num_houses] = santa_house;
            num_houses++;
        }

        if (check_for_house(houses, num_houses, robo_house)) {
            houses[num_houses] = robo_house;
            num_houses++;
        }

        move_house(&santa_house, data[i]);
        i++;
        move_house(&robo_house, data[i]);
        i++;
    }
    printf("%d houses were visited (p2)!\n", num_houses);

    return 0;
}