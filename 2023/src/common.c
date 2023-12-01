#include <stdio.h>
#include <stdlib.h>

int get_data(const char* filename, char** data) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Failed to open file %s!\n", filename);
        return -1;
    }

    if (fseek(fp, 0L, SEEK_END) != 0) {
        printf("Failed to seek to end of file!\n");
        return -1;
    }

    size_t size = ftell(fp);

    if (fseek(fp, 0L, SEEK_SET) != 0) {
        printf("Failed to seek to beginning of file!\n");
        return -1;
    }

    *data = malloc(size + 1);
    if (*data == NULL) {
        printf("Failed to allocate memory!\n");
        return -1;
    }
    (*data)[size] = '\0';

    size_t bytes_read = fread(*data, sizeof(char), size, fp);
    if (size != bytes_read) {
        printf("Expected to read %lu bytes but only read %lu!\n", size, bytes_read);
        return -1;
    }

    if (fclose(fp) != 0) {
        printf("Failed to close file!\n");
        return -1;
    }

    return 0;
}