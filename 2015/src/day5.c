#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>

#include "common.h"

int is_nice_string(char* str) {
    int len = strlen(str);
    int vowels = 0;
    bool has_double = false;
    for (int i = 0; i < len; i++) {
        switch (str[i]) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            vowels++;
        }

        if (str[i] == str[i + 1]) {
            has_double = true;
        }

        if (str[i] == 'a' && str[i + 1] == 'b') {
            return false;
        } else if (str[i] == 'c' && str[i + 1] == 'd') {
            return false;
        } else if (str[i] == 'p' && str[i + 1] == 'q') {
                return false;
        } else if (str[i] == 'x' && str[i + 1] == 'y') {
                return false;
        }
    }

    if (has_double && vowels >= 3) {
        return true;
    } else {
        return false;
    }
}

bool p2_rule1(char* str) {
    int len = strlen(str);
    for (int i = 2; i < len; i++) {
        if (str[0] == str[i] && str[1] == str[i + 1]) {
            return true;
        }
    }

    return false;
}

bool p2_rule2(char* str) {
    if (strlen(str) > 2 && str[0] == str[2]) {
        return true;
    }

    return false;
}

bool is_nice_string_p2(char* str) {
    int len = strlen(str);
    bool r1 = false;
    bool r2 = false;
    for (int i = 0; i < len; i++) {
        if (!r1 && p2_rule1(str + i)) {
            r1 = true;
        }

        if (!r2 && p2_rule2(str + i)) {
            r2 = true;
        }
    }

    return r1 && r2;
}
int main() {
    char* data;
    if (get_data("data/day5.txt", &data) != 0) {
        printf("Failed to get data!\n");
        return -1;
    }

    char* token =strtok(data, "\n");
    int nice_strings = 0;
    int nice_strings_p2 = 0;
    while (token) {
        if (is_nice_string(token)) {
            nice_strings++;
        }

        if (is_nice_string_p2(token)) {
            nice_strings_p2++;
        }
        token = strtok(NULL, "\n");
    }

    printf("%d nice strings!\n", nice_strings);
    printf("%d nice strings p2!\n", nice_strings_p2);
    free(data);

    return 0;
}