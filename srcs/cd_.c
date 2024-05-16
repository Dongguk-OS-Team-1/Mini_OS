#include "bases.h"
#include "cd_.h"

void    error_detect(void);

void  cd_(int argc, char* argv[]) {

    if (argc == 2) {
        // '/' 루트 디렉토리로 이동
        if (strcmp(argv[1], "/") == 0) {
            if (chdir("/") != 0) {
                error_detect_cd();
                return 1;
            }
        }
        // '.' 현재 디렉토리로 이동
        else if (strcmp(argv[1], ".") == 0) {   }
        // '..' 상위 디렉토리로 이동
        else if (strcmp(argv[1], "..") == 0) {
            if (chdir("..") != 0) {
                error_detect_cd();
                    return 1;
            }
        }
        //해당 디렉토리로 이동
        else {
            if (chdir(argv[1]) != 0) {
                error_detect_cd();
                    return 1;
            }
        }
    }
    // '~' or ' ' 홈 디렉토리로 이동
    else if (argc == 1 || (argc == 2 && strcmp(argv[1], "~") == 0)) {
        if (chdir(getenv("HOME")) != 0) {
            error_detect_cd();
            return 1;
        }
    }
     
    else {
        fprintf(stderr, "usage: cd directory_name ...\n");
        return 1;
    }
}

void    error_detect(void) {
    switch (errno) {
        case EACCES:
            fprintf(stderr, "Error: Permission denied to change directory.\n");
            break;
        case ELOOP:
            fprintf(stderr, "Error: Too many symbolic links encountered.\n");
            break;
        case ENAMETOOLONG:
            fprintf(stderr, "Error: Pathname is too long.\n");
            break;
        case ENOENT:
            fprintf(stderr, "Error: Directory does not exist.\n");
            break;
        case ENOTDIR:
            fprintf(stderr, "Error: A component of the path is not a directory.\n");
            break;
        default:
            perror("cd failed");
            fprintf(stderr, "Error: %s\n", strerror(errno));
    }
}