/* ************************************************************************** */
/*                                                                            */
/*                                  rmdir_.c                                  */
/*                                                                            */
/*                       By: 최정흠 <andyc707@dgu.ac.kr>                      */
/*                                                                            */
/*                        Created: 2024/05/20 15:10:12                        */
/*                                                                            */
/* ************************************************************************** */

#include "bases.h"
#include "rmdir_.h"

int     collapse_dir(char *path_org, char *target);
int     collapse_brace_dir(char *real_path, int find_dirname, int start, int end);
int     is_absolute_path(const char *path);
void    *pthread_rmdir_func(void *arg_);
void    error_detect_rmdir(char *target);
void    print_log_rmdir(FILE *dirFile, char *dir_name);

void  rmdir_(int argc, char *argv[]) {

    int     p_flag;
    int     returned_opt;
    int     success;
    int     dirfd;
    int     i;
    int     path_len;
    int     start, end;
    char    real_path[MAX];
    char    *temp;
    int     res;

    // Initialize getopt's external variables
    optind = 1;
    optopt = '\0';
    optarg = NULL;

    p_flag = 0;

    // Parsing options using getopt()
    while ((returned_opt = getopt(argc, argv, "p")) != -1)
        switch (returned_opt) {
            case 'p':
                p_flag = 1;
                break ;
            case '?':
            default:
                fprintf(stderr, "usage: rmdir [-p] directory_name ...\n");
                return ;
        }

    // Move the pointer to the path
    argc -= optind;
    argv += optind;

    if (*argv == NULL) {
        fprintf(stderr, "usage: rmdir [-p] directory_name ...\n");
        return ;
    }

    for ( ; argc > 0; argc--, argv++) {

        success = 1;
        
        // Trim trailing slashes from the path.
        temp = strrchr(*argv, '\0');
        while (--temp > *argv && *temp == '/')
            *temp = '\0';

        // Check if the directory name is a relative path
        if (!is_absolute_path(*argv))
            realpath(*argv, real_path); // transfrom to real path
        else if (!p_flag)
            strcpy(real_path, *argv);

        if (p_flag)
            success = collapse_dir(real_path, *argv);
        else { // Case of don't need to make subdirectory
            path_len = (int)strlen(real_path);

            // Find dirname{%d..%d} pattern
            if (find_brace_pattern(real_path, &start, &end)) {
                path_len = (int)strlen(real_path);
                for (i = path_len; i >= 0; i--)
                    if (real_path[i] == '/') {
                        real_path[i] = '\0';
                        i++;
                        break;
                    }
                success = collapse_brace_dir(real_path, i, start, end);
            } else { // input dosen't have dirname{%d..%d} pattern
                if ((dirfd = open(real_path, O_RDONLY)) != -1) {
                    res = syscall(SYS_rmdir, real_path);
                    if (res < 0)
                        success = 0;
                    else {
                        FILE* dirFile = fopen("resources/log.txt", "a+");
                        if (dirFile == NULL)
                            perror("can't open log.txt");
                        else
                            print_log_rmdir(dirFile, real_path);
                    }
                    close(dirfd);
                }
                else
                    success = 0;
            }
        }
        if (!success)
            error_detect_rmdir(*argv);
    }

    return ;
}

/**
 *  Builds directories based on the given path.
 *
 *  Inputs:
 *      char *path_org
 *          The path where directories will be created.
 *
 *  Returns:
 *      Returns 1 if the directories are created successfully.
 *      Returns 0 if an error occurs during the creation of directories.
 *
 *  Notes:
 *      - This function creates directories based on the given path.
 *      - The 'path_org' parameter indicates the path where directories will be created.
 *      - The 'mode' parameter specifies the file permission mode for the directories.
 *      - If intermediate directories in the path do not exist, they will be created.
 *      - If the path already exists as a directory, an error message will be printed.
 */
int collapse_dir(char *path_org, char *target) {

    // path_stat : is structure to store file/directory information
    // struct stat path_stat;
    // dirfd : is file descriptor for the directory.
    int         dirfd;
    // Pointers to manipulate the path string
    char        *path, *end_path_org, *temp;
    // res : is syscall function's return value
    int         res;
    // char *dir_name;
    const int   len_path_org = strlen(path_org);
    const int   len_target = strlen(target);
    int         i;
    int         j;

    // Check Path is exist
    if ((dirfd = open(path_org, O_RDONLY)) != -1)
        close(dirfd);
    else
        return (0);

    if (len_path_org < len_target) // Need ERROR SETTING
        return (0);

    i = len_path_org - 1;
    j = len_target - 1;
    for ( ; j >= 0; i--, j--)
        if (path_org[i] != target[j]) // Need ERROR SETTING
            return (0);
    end_path_org = path_org + i;

    // Trim trailing slashes from the path.
    temp = strrchr(path_org, '\0');
    while (--temp > path_org && *temp == '/')
        *temp = '\0';

    path = path_org + (int)strlen(path_org) - 1;

    for ( ; path >= end_path_org; path--) {
        if (*path != '/')
            continue ;

        if ((res = syscall(SYS_rmdir, path_org)) != 0)
            return (0);

        FILE* dirFile = fopen("resources/log.txt", "a+");
        if (dirFile == NULL)
            perror("can't open log.txt");
        else
            print_log_rmdir(dirFile, path + 1);
        *path = '\0';
    }

    return (1);
}

/**
 *  Builds multiple directories with a brace pattern.
 *  The function creates directories based on the given brace pattern
 *  and a range of numbers.
 *
 *  Inputs:
 *      char  *real_path
 *         The path where the directories will be created.
 *
 *      int find_dirname
 *         The index of the directory name in the 'real_path' string.
 *
 *      int start
 *          The starting number of the range for creating directories.
 *
 *      int end
 *          The ending number of the range for creating directories.
 *
 *  Return:
 *      Returns 1 if the directories are created successfully.
 *      Returns 0 if an error occurs during the creation of directories.
 *
 *  Notes:
 *      - The function uses a brace pattern and a range of numbers to create multiple directories.
 *      - The 'mode' parameter specifies the file permission mode for the directories.
 *      - The 'real_path' parameter indicates the path where the directories will be created.
 *      - The 'find_dirname' parameter is the index of the directory name in the 'real_path' string.
 *      - The 'start' and 'end' parameters define the range of numbers for creating directories.
 *      - The function creates directories in parallel using multiple threads.
 *      - The function returns 0 if the range of numbers is invalid or if an error occurs during directory creation.
 */
int collapse_brace_dir(char *real_path, int find_dirname, int start, int end) {

    char  dir_name[MAX];

    // brc_pt_cnt : is the number of directories to create from the brace pattern.
    int brc_pt_cnt;
    if ((brc_pt_cnt = end - start + 1) <= 0) {
        fprintf(stderr, "Invalid dirname{%d..%d}\n", start, end);
        return (0);
    }

    pthread_t   *thread_ids;
    ThreadArgs  *thread_args;
    thread_ids = (pthread_t *) malloc(sizeof(pthread_t) * brc_pt_cnt);
    thread_args = (ThreadArgs *) malloc(sizeof(ThreadArgs) * brc_pt_cnt);

    // dirfd: is used to verify the path of the directory
    //          to be created and to create the directory.
    int dirfd;
    if ((dirfd = open(real_path, O_RDONLY)) == -1) {
        fprintf(stderr, "open func failed\n");
        return (0);
    }

    // res: is used for exception.
    int res;
    int j;
    // Get a directory name from real_path
    strcpy(dir_name, strtok(real_path + find_dirname, "{"));
    for (j = 0; j < brc_pt_cnt; j++) {
        /**
         *  Make args for thread.
         */
        sprintf(thread_args[j].dir_name, "%s/%s%d", real_path, dir_name, start + j);

        res = pthread_create(&thread_ids[j], NULL, pthread_rmdir_func, (void *)&thread_args[j]);
        if (res != 0) {
            perror("Failed to create thread");
            return (0);
        }
    }

    res = 0;
    for (j = 0; j < brc_pt_cnt; j++) {
        res = pthread_join(thread_ids[j], NULL);
        if (res != 0) {
            perror("Failed to join thread");
            return (0);
        } else {
            FILE* dirFile = fopen("resources/log.txt", "a+");
            if (dirFile == NULL)
                perror("can't open log.txt");
            else
                print_log_rmdir(dirFile, thread_args[j].dir_name);
        }
    }

    close(dirfd);
    free(thread_ids);
    free(thread_args);

    return (1);
}

void *pthread_rmdir_func(void *arg_) {

    ThreadArgs *arg = (ThreadArgs *) arg_;

    int result = syscall(SYS_rmdir, arg->dir_name);
    if (result < 0) {
        perror("rmdir");
        pthread_exit((void *)1);
    }

    pthread_exit(NULL);
}

void error_detect_rmdir(char *target) {
    switch (errno) {
        case EACCES:
            fprintf(stderr, "rmdir: %s: Permission denied to remove directory.\n", target);
            break ;
        case ENOENT:
        case ENOTDIR:
            fprintf(stderr, "rmdir: %s: No such file or directory.\n", target);
            break ;
        case ENOTEMPTY:
            fprintf(stderr, "rmdir: %s: Directory not empty.\n", target);
            break ;
        default:
            fprintf(stderr, "rmdir: %s: %s\n", target, strerror(errno));
    }
}

void print_log_rmdir(FILE *dirFile, char *dir_name) {

    char line[MAX];
    int nameExists = 0;
    while (fgets(line, MAX, dirFile) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        if (strcmp(line + 2, dir_name) == 0) {
            nameExists = 1;
            break ;
        }
    }
    fclose(dirFile);

    if (!nameExists) {
        dirFile = fopen("resources/log.txt", "a");
        if (dirFile == NULL) {
            perror("can't open log.txt");
            return ;
        }
        fprintf(dirFile, "d %s\n", dir_name);
        fclose(dirFile);
    }

    return ;
}

