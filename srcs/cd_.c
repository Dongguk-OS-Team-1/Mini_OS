#include "bases.h"
#include "cd_.h"

void    error_detect_cd(void);

void  cd_(int argc, char* argv[]) {

    if (argc == 2) {
        // Change to root directory
        if (strcmp(argv[1], "/") == 0) {
            if (chdir("/") != 0) {
                error_detect_cd();
                return ;
            }
        }
        // '.' Change to current directory
        else if (strcmp(argv[1], ".") == 0) {   }
        // '..' Change to parent directory
        else if (strcmp(argv[1], "..") == 0) {
            if (chdir("..") != 0) {
                error_detect_cd();
                    return ;
            }
        }
        //Change directory based on the provided path
        else {
            if (chdir(argv[1]) != 0) {
                error_detect_cd();
                    return ;
            }
        }
    }
    //Change to home directory
    else if (argc == 1) {
        if (chdir(getenv("HOME")) != 0) {
            error_detect_cd();
            return ;
        }
    }
     
    else {
        fprintf(stderr, "usage: cd directory_name ...\n");
        return ;
    }
}

void    error_detect_cd(void) {
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