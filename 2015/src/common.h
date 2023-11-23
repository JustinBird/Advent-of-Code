#include <stdint.h>

/**
 * Gets all data from \p filename and copies it into new memory in \p data.
 *
 * @param filename The name of the file to read.
 * @param [out] data The address where the new memory location is written.
 *
 * @return 0 on success, -1 on failure.
 */
uint32_t get_data(const char* filename, char** data);