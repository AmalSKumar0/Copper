#include "include/io.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* get_file_contents(const char* filename) {
    // Check if filename ends with ".cop"
    const char* extension = strrchr(filename, '.'); // find last '.'
    if (extension == NULL || strcmp(extension, ".cop") != 0) {
        fprintf(stderr, "Error: Invalid file type. Expected a .cop file.\n");
        return NULL;
    }

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    // Move to end of file to determine size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    // Allocate memory for file content + null terminator
    char* buffer = (char*)malloc((fileSize + 1) * sizeof(char));
    if (buffer == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    // Read file content
    size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
    buffer[bytesRead] = '\0'; // Null-terminate

    fclose(file);
    return buffer;
}
