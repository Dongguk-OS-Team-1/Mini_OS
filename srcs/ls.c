#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include "ls.h"

// 파일 이름 비교 함수
int compare_names(const void *a, const void *b) {
    struct dirent *entryA = *(struct dirent **)a;
    struct dirent *entryB = *(struct dirent **)b;

    // Makefile을 알파벳 순서에 맞추도록 특별히 처리
    if (strcmp(entryA->d_name, "Makefile") == 0) return strcmp("makefile", entryB->d_name);
    if (strcmp(entryB->d_name, "Makefile") == 0) return strcmp(entryA->d_name, "makefile");

    return strcmp(entryA->d_name, entryB->d_name);
}

void list_directory(int argc, char **argv) {
    struct dirent **namelist;
    int n;
    int show_all = 0;
    int show_almost_all = 0;
    int long_format = 0;
    int show_inode = 0;

    // 옵션 파싱
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-a") == 0) {
            show_all = 1;
        } else if (strcmp(argv[i], "-A") == 0) {
            show_almost_all = 1;
        } else if (strcmp(argv[i], "-l") == 0) {
            long_format = 1;
        } else if (strcmp(argv[i], "-i") == 0) {
            show_inode = 1;
        } else if (strcmp(argv[i], "-al") == 0 || strcmp(argv[i], "-la") == 0) {
            show_all = 1;
            long_format = 1;
        } else if (strcmp(argv[i], "-Al") == 0 || strcmp(argv[i], "-lA") == 0) {
            show_almost_all = 1;
            long_format = 1;
        } else if (strcmp(argv[i], "-ail") == 0 || strcmp(argv[i], "-ali") == 0 || strcmp(argv[i], "-ila") == 0 || strcmp(argv[i], "-lai") == 0 || strcmp(argv[i], "-ial") == 0 || strcmp(argv[i], "-lia") == 0) {
            show_all = 1;
            long_format = 1;
            show_inode = 1;
        } else if (strcmp(argv[i], "-Ail") == 0 || strcmp(argv[i], "-Ali") == 0 || strcmp(argv[i], "-iAl") == 0 || strcmp(argv[i], "-ilA") == 0 || strcmp(argv[i], "-lAi") == 0 || strcmp(argv[i], "-liA") == 0) {
            show_almost_all = 1;
            long_format = 1;
            show_inode = 1;
        } else {
            printf("invalid option: %s\n", argv[i]);
            return;
        }
    }

    // 현재 디렉토리 스캔
    n = scandir(".", &namelist, NULL, alphasort);
    if (n < 0) {
        perror("scandir");
        return;
    }

    // Makefile이 알파벳 순서에 맞춰지도록 정렬
    qsort(namelist, n, sizeof(struct dirent *), compare_names);

    // 파일 목록 출력
    for (int i = 0; i < n; i++) {
        if (!show_all && !show_almost_all && namelist[i]->d_name[0] == '.') {
            free(namelist[i]);
            continue;
        }

        if (show_almost_all && (strcmp(namelist[i]->d_name, ".") == 0 || strcmp(namelist[i]->d_name, "..") == 0)) {
            free(namelist[i]);
            continue;
        }

        if (show_inode) {
            printf("%lu ", namelist[i]->d_ino);
        }

        if (long_format) {
            struct stat st;
            stat(namelist[i]->d_name, &st);

            // 파일 유형 및 권한 출력
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

            // 소유자 및 그룹 출력
            struct passwd *pw = getpwuid(st.st_uid);
            struct group *gr = getgrgid(st.st_gid);
            if (pw != NULL && gr != NULL) {
                printf(" %s %s", pw->pw_name, gr->gr_name);
            } else {
                printf(" %d %d", st.st_uid, st.st_gid);
            }

            // 파일 크기 출력
            printf(" %5ld", st.st_size);

            // 수정 시간 출력
            char timebuf[80];
            struct tm *tm;
            tm = localtime(&st.st_mtime);
            strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", tm);
            printf(" %s", timebuf);

            // 파일 이름 출력
            printf(" %s\n", namelist[i]->d_name);
        } else {
            // 파일 이름만 출력
            printf("%s  ", namelist[i]->d_name);
        }

        free(namelist[i]);
    }

    if (!long_format) {
        printf("\n");  // 가로 출력 후 개행
    }

    free(namelist);
}
