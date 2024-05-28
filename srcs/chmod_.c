#include"chmod_.h"

mode_t convert_mode_str_to_oct(const char *mode_str) {
    char *endptr;
    errno = 0;
    long mode = strtol(mode_str, &endptr, 8);

    // strtol이 변환한 값이 유효한지 검사
    if (errno != 0 || *endptr != '\0' || mode < 0 || mode > 07777) {
        return (mode_t)-1; // 유효하지 않은 경우 -1 반환
    }

    return (mode_t)mode;
}

int chmod_(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Error\n"); // 인자가 3개 입력되어야 하는데 적게 입력될 경우.
        return -1;
    }

    struct stat file_stat;
    if (stat(argv[2], &file_stat) == -1) {
        printf("Can't access to %s\n", argv[2]); // argv[2] 이름의 파일이 존재하지 않으면 오류
        return -1;
    }

    mode_t new_mode = file_stat.st_mode;
    if (argv[1][0] >= '0' && argv[1][0] <= '9') { // absolute mode
        mode_t mode;
        if ((mode = convert_mode_str_to_oct(argv[1])) == -1) {
            fprintf(stderr, "Invalid parameter\n");
            return -1;
        }

        if (chmod(argv[2], mode) == -1) {
            perror("chmod");
            return -1;
        }
    } else { // symbolic mode
        char *token = strtok(argv[1], ", ");
        while (token != NULL) {
            char who = token[0];
            char op = token[1];
            for (int i = 2; token[i] != '\0'; i++) {
                mode_t perm = 0;
                switch (token[i]) {
                    case 'r': perm = (who == 'u') ? S_IRUSR : (who == 'g') ? S_IRGRP : S_IROTH; break;
                    case 'w': perm = (who == 'u') ? S_IWUSR : (who == 'g') ? S_IWGRP : S_IWOTH; break;
                    case 'x': perm = (who == 'u') ? S_IXUSR : (who == 'g') ? S_IXGRP : S_IXOTH; break;
                }

                if (op == '+') {
                    new_mode |= perm;
                } else if (op == '-') {
                    new_mode &= ~perm;
                } else if (op == '=') {
                    if (who == 'u') new_mode &= ~(S_IRUSR | S_IWUSR | S_IXUSR);
                    else if (who == 'g') new_mode &= ~(S_IRGRP | S_IWGRP | S_IXGRP);
                    else if (who == 'o') new_mode &= ~(S_IROTH | S_IWOTH | S_IXOTH);
                    new_mode |= perm;
                }
            }
            token = strtok(NULL, ", ");
        }

        if (chmod(argv[2], new_mode) == -1) {
            perror("chmod");
            return -1;
        }
    }

    return 0;
}
