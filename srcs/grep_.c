#include "grep_.h"

#define MAX_LINE_LENGTH 1024

void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void grep_impl(const char *pattern, const char *file_path, int options) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file '%s'\n", file_path);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    int line_number = 1;
    char *lowercase_pattern = NULL;
    if (options & 1) { // Check if ignore_case option is enabled
        lowercase_pattern = strdup(pattern);
        to_lowercase(lowercase_pattern);
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        char *line_copy = strdup(line);
        if (options & 1) { // Check if ignore_case option is enabled
            to_lowercase(line_copy);
        }

        bool match = (strstr(options & 1 ? line_copy : line, options & 1 ? lowercase_pattern : pattern) != NULL);

        if (options & 2) { // Check if invert_match option is enabled
            match = !match;
        }

        if (match) {
            if (options & 4) { // Check if show_line_numbers option is enabled
                printf("%d:", line_number);
            }
            printf("%s", line);
        }

        free(line_copy);
        line_number++;
    }

    if (options & 1) { // Check if ignore_case option is enabled
        free(lowercase_pattern);
    }
    fclose(file);
}

int grep_(int argc, char *argv[]) {
    if (argc < 3 || argc > 6) {
        fprintf(stderr, "Usage: %s [-i] [-v] [-n] <pattern> <file1> [<file2> ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int options = 0;
    int arg_start_index = 1;

    // 옵션 파싱
    while (arg_start_index < argc && argv[arg_start_index][0] == '-') {
        for (int i = 1; argv[arg_start_index][i]; i++) {
            if (argv[arg_start_index][i] == 'i') {
                options |= 1; // Set ignore_case option bit
            } else if (argv[arg_start_index][i] == 'v') {
                options |= 2; // Set invert_match option bit
            } else if (argv[arg_start_index][i] == 'n') {
                options |= 4; // Set show_line_numbers option bit
            } else {
                fprintf(stderr, "Unknown option: -%c\n", argv[arg_start_index][i]);
                exit(EXIT_FAILURE);
            }
        }
        arg_start_index++;
    }

    if (arg_start_index >= argc - 1) {
        fprintf(stderr, "Usage: %s [-i] [-v] [-n] <pattern> <file1> [<file2> ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *pattern = argv[arg_start_index++];

    // 각 파일에 대해 grep 실행
    for (int i = arg_start_index; i < argc; i++) {
        char *file_path = argv[i];
        grep_impl(pattern, file_path, options);
    }

    return 0;
}

