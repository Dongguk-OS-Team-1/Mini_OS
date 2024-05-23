#include <stdio.h>

#include <stdlib.h>

#include <dirent.h>

#include <sys/stat.h>

#include <string.h>

#include <time.h>

#include <pwd.h> 

#include <grp.h> 

#include "ls.h"



void list_directory(int argc, char **argv) {

    struct dirent **namelist;

    int n;

    int show_all = 0;

    int long_format = 0;



    for (int i = 1; i < argc; i++) {

        if (strcmp(argv[i], "-a") == 0) {

            show_all = 1;

        } else if (strcmp(argv[i], "-l") == 0) {

            long_format = 1;

        } else if (strcmp(argv[i], "-al") == 0 || strcmp(argv[i], "-la") == 0) {

            show_all = 1;

            long_format = 1;

        } else {

            printf("invalid option: %s\n", argv[i]);

            return;

        }

    }



    n = scandir(".", &namelist, NULL, alphasort);

    if (n < 0) {

        perror("scandir");

        return;

    }



    while (n--) {

        if (!show_all && namelist[n]->d_name[0] == '.') {

            free(namelist[n]);

            continue;

        }



        if (long_format) {

            struct stat st;

            stat(namelist[n]->d_name, &st);



            printf((S_ISDIR(st.st_mode)) ? "d" : "-");

            printf((st.st_mode & S_IRUSR) ? "r" : "-");

            printf((st.st_mode & S_IWUSR) ? "w" : "-");

            printf((st.st_mode & S_IXUSR) ? "x" : "-");

            printf((st.st_mode & S_IRGRP) ? "r" : "-");

            printf((st.st_mode & S_IWGRP) ? "w" : "-");

            printf((st.st_mode & S_IXGRP) ? "x" : "-");

            printf((st.st_mode & S_IROTH) ? "r" : "-");

            printf((st.st_mode & S_IWOTH) ? "w" : "-");

            printf((st.st_mode & S_IXOTH) ? "x" : "-");

            printf(" %2ld", st.st_nlink);



            

            struct passwd *pw = getpwuid(st.st_uid);

            struct group *gr = getgrgid(st.st_gid);

            if (pw != NULL && gr != NULL) {

                printf(" %s %s", pw->pw_name, gr->gr_name);

            } else {

                printf(" %d %d", st.st_uid, st.st_gid);

            }



            printf(" %5ld", st.st_size);



            char timebuf[80];

            struct tm *tm;

            tm = localtime(&st.st_mtime);

            strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", tm);

            printf(" %s", timebuf);



            printf(" %s\n", namelist[n]->d_name);

        } else {

            printf("%s\n", namelist[n]->d_name);

        }



        free(namelist[n]);

    }

    free(namelist);

}