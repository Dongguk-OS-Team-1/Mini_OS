#include "chmod_.h"

void print_usage(char *program_name) {
    printf("Usage: %s <mode> <filename>\n", program_name);
    printf("Modes: symbolic (e.g., u+rwx,g+rx,o-w) or numeric (e.g., 755)\n");
}

mode_t parse_symbolic_mode(char *mode_str) {
    mode_t mode = 0;

    while (*mode_str) {
        switch (*mode_str++) {
            case 'u':
                mode |= S_IRUSR | S_IWUSR | S_IXUSR;
                break;
            case 'g':
                mode |= S_IRGRP | S_IWGRP | S_IXGRP;
                break;
            case 'o':
                mode |= S_IROTH | S_IWOTH | S_IXOTH;
                break;
            case 'a':
                mode |= S_IRUSR | S_IWUSR | S_IXUSR |
                        S_IRGRP | S_IWGRP | S_IXGRP |
                        S_IROTH | S_IWOTH | S_IXOTH;
                break;
            case '+':
                break;
            case '-':
                break;
            case '=':
                mode = 0;
                break;
            case 'r':
                mode |= S_IRUSR | S_IRGRP | S_IROTH;
                break;
            case 'w':
                mode |= S_IWUSR | S_IWGRP | S_IWOTH;
                break;
            case 'x':
                mode |= S_IXUSR | S_IXGRP | S_IXOTH;
                break;
            default:
                fprintf(stderr, "Invalid mode: %c\n", *(mode_str - 1));
                exit(EXIT_FAILURE);
        }
    }

    return mode;
}

mode_t parse_numeric_mode(char *mode_str) {
    // strtol을 사용하여 mode_str을 정수로 변환
    return (mode_t)strtol(mode_str, NULL, 8);
}

int chmod_(int argc, char *argv[]) {
    if (argc != 3) {
        print_usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    char *mode_str = argv[1];
    char *file_name = argv[2];
    mode_t mode;

    // symbolic mode인지 numeric mode인지 확인
    if (mode_str[0] == '-') {
        mode = parse_numeric_mode(mode_str + 1);
    } else {
        mode = parse_symbolic_mode(mode_str);
    }

    if (chmod(file_name, mode) == -1) {
        perror("chmod");
        exit(EXIT_FAILURE);
    }

    printf("Permissions of '%s' changed successfully.\n", file_name);

    return 0;
}
