#include "grep_.h"
#define MAX_LINE_LENGTH 1024

void grep_impl(const char *pattern, const char *file_path, bool ignore_case, bool invert_match, bool show_line_numbers) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file '%s'\n", file_path);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    int line_number = 1;
    while (fgets(line, sizeof(line), file) != NULL) {
        char *line_copy = strdup(line); // 원본 라인을 유지하기 위해 복사본 사용
        char *line_to_check = line_copy;

        if (ignore_case) {
            // 대소문자를 구분하지 않고 비교하기 위해 소문자로 변환
            for (int i = 0; line_to_check[i]; i++) {
                line_to_check[i] = tolower(line_to_check[i]);
            }
            char *lowercase_pattern = strdup(pattern);
            for (int i = 0; lowercase_pattern[i]; i++) {
                lowercase_pattern[i] = tolower(lowercase_pattern[i]);
            }
            pattern = lowercase_pattern;
        }

        bool match = (strstr(line_to_check, pattern) != NULL);

        if (invert_match) {
            match = !match;
        }

        if (match) {
            if (show_line_numbers) {
                printf("%d:", line_number);
            }
            printf("%s", line);
        }

        free(line_copy);
        if (ignore_case) {
            free((char *)pattern); // 메모리 해제
        }
        line_number++;
    }

    fclose(file);
}

int grep_(int argc, char *argv[]) {
    if (argc < 3 || argc > 6) {
        fprintf(stderr, "Usage: %s [-i] [-v] [-n] <pattern> <file1> [<file2> ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    bool ignore_case = false;
    bool invert_match = false;
    bool show_line_numbers = false;
    int arg_start_index = 1;

    // 옵션 파싱
    if (argc >= 4 && strcmp(argv[1], "-i") == 0) {
        ignore_case = true;
        arg_start_index++;
    }

    if (argc >= 4 && strcmp(argv[arg_start_index], "-v") == 0) {
        invert_match = true;
        arg_start_index++;
    }

    if (argc >= 4 && strcmp(argv[arg_start_index], "-n") == 0) {
        show_line_numbers = true;
        arg_start_index++;
    }

    char *pattern = argv[arg_start_index++];
    
    // 각 파일에 대해 grep 실행
    for (int i = arg_start_index; i < argc; i++) {
        char *file_path = argv[i];
        grep_impl(pattern, file_path, ignore_case, invert_match, show_line_numbers);
    }

    return 0;
}
