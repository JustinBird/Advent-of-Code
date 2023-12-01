#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>

#include "common.h"

int is_spelled_out(char* str) {
    char* words[] = {
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine",
        "ten"
    };

    for (int i = 0; i < sizeof(words) / sizeof(char*); i++) {
        if (strncmp(str, words[i], strlen(words[i])) == 0) {
            return i + 1;
        }
    }

    return 0;
}
int get_first_digit(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        int spelled_out = is_spelled_out(str + i);
        if (spelled_out) {
            return spelled_out;
        }

        if (str[i] >= '0' && str[i] <= '9') {
            printf("First digit is %d\n", str[i] - '0');
            return str[i] - '0';
        }
    }

    return -1;
}

int get_last_digit(char* str) {
    int len = strlen(str);
    for (int i = len - 1; i >= 0; i--) {
        int spelled_out = is_spelled_out(str + i);
        if (spelled_out) {
            return spelled_out;
        }

        if (str[i] >= '0' && str[i] <= '9') {
            printf("Last digit is %d\n", str[i] - '0');
            return str[i] - '0';
        }
    }

    return -1;
}

int main() {
    char* data;
    if (get_data("data/day1.txt", &data) != 0) {
        printf("Failed to get data!\n");
        return -1;
    }

    int sum = 0;
    char* token = strtok(data, "\n");
    while (token) {
        sum += (get_first_digit(token) * 10) + get_last_digit(token);
        token = strtok(NULL, "\n");
    }

    printf("%d total!\n", sum);
    free(data);

    return 0;
}