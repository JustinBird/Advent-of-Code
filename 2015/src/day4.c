#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>

#include "common.h"

#define MD5SUM_LENGTH 32

int md5sum(char* input, char** output) {
    int md5sum_input[2];
    int md5sum_output[2];
    if (pipe(md5sum_input) < 0 || pipe(md5sum_output) < 0) {
        perror("pipe");
        printf("Failed to open pipe!\n");
    }

    pid_t p = fork();
    if (p < 0) {
        perror("fork");
        return 1;
    } else if (p == 0) {
        if (close(md5sum_input[1]) != 0 || close(md5sum_output[0]) != 0) {
            perror("close");
            printf("Failed to close md5sum writing input or reading output!\n");
            return 1;
        }

        if (dup2(md5sum_input[0], STDIN_FILENO) == -1 || dup2(md5sum_output[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            printf("Failed to set point stdin to md5sum input!\n");
            return 1;
        }

        if (close(md5sum_input[0]) != 0 || close(md5sum_output[1]) != 0) {
            perror("close");
            printf("Failed to close md5sum reading input or writing output!\n");
            return 1;
        }

        if (execlp("md5sum", "md5sum", NULL) != 0) {
            perror("execl");
            printf("Failed to run md5sum!\n");
            return 1;
        }
        exit(0);
    } else {
        if (close(md5sum_input[0]) != 0 || close(md5sum_output[1]) != 0) {
            perror("close");
            printf("Failed to close md5sum reading input or writing output!\n");
            return 1;
        }

        ssize_t bytes_written = write(md5sum_input[1], input, strlen(input));
        if (bytes_written != strlen(input)) {
            perror("write");
            printf("Failed to write to md5sum input!\n");
            return 1;
        }

        if (close(md5sum_input[1]) != 0) {
            perror("close");
            printf("Failed to close md5sum input!\n");
            return 1;
        }

        *output = malloc(sizeof(char) * (MD5SUM_LENGTH + 1));
        if (*output == NULL) {
            printf("Failed to allocate memory!\n");
            return 1;
        }
        (*output)[MD5SUM_LENGTH] = '\0';

        size_t bytes_read = read(md5sum_output[0], *output, MD5SUM_LENGTH);
        if (bytes_read != MD5SUM_LENGTH) {
            printf("Read %ld bytes but wanted %d!\n", bytes_read, MD5SUM_LENGTH);
            return 1;
        }

        if (close(md5sum_output[0]) != 0) {
            perror("close");
            printf("Failed to close md5sum output!\n");
            return 1;
        }

        int status;
        wait(&status);
        if (status != 0) {
            printf("md5sum failed to run!\n");
            return 1;
        }

        return 0;
    }
}

int zero_hash(char* hash) {
    for (int i = 0; i < 6; i++) {
        if (hash[i] != '0') {
            return 0;
        }
    }

    return 1;
}

int main() {
    char* data;
    if (get_data("data/day4.txt", &data) != 0) {
        printf("Failed to get data!\n");
        return -1;
    }

    char* input = malloc(128);
    if (input == NULL) {
        printf("Failed to allocate memory!\n");
        return 1;
    }

    int count = 282749;
    memcpy(input, data, strlen(data));
    while (true) {
        snprintf(input + strlen(data), 128, "%d", count);
        if (count % 100 == 0) {
            printf("hashing %s\n", input);
        }

        char* hash;
        if (md5sum(input, &hash)) {
            printf("Failed to get md5sum!\n");
            return 1;
        }

        if (zero_hash(hash)) {
            printf("hash: %s\n", hash);
            printf("Found zero hash with input %s\n", input);
            break;
        }
        free(hash);

        count+= 1;
    }

    free(input);
    free(data);

    return 0;
}