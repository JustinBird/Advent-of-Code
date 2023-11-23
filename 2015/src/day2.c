#include <stdio.h>
#include <string.h>

#include "common.h"

int main() {
    char* data;
    if (get_data("data/day2.txt", &data) != 0) {
        printf("Failed to get data!\n");
        return -1;
    }

    char* delim = "\n";
    char* token;

    int paper = 0;
    int ribbon = 0;
    token = strtok(data, delim);
    while (token != NULL) {
        int l, w, h = 0;
        if (sscanf(token, "%dx%dx%d", &l, &w, &h) != 3) {
            printf("Failed to parse input!\n");
            return -1;
        }
        int side1 = l * w;
        int side2 = w * h;
        int side3 = h * l;
        paper += (2 * side1) + (2 * side2) + (2 * side3);
        int slack = side1;
        if (side2 < slack) {
            slack = side2;
        }
        if (side3 < slack) {
            slack = side3;
        }
        paper += slack;

        int perim1 = (2 * l) + (2 * w);
        int perim2 = (2 * w) + (2 * h);
        int perim3 = (2 * h) + (2 * l);
        int perim = perim1;
        if (perim2 < perim) {
            perim = perim2;
        }
        if (perim3 < perim) {
            perim = perim3;
        }
        ribbon += perim + (l * w * h);

        token = strtok(NULL, delim);
    }

    printf("Total paper needed is %d\n", paper);
    printf("Total ribbon needed is %d\n", ribbon);
    return 0;
}