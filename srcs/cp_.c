#include "bases.h"
#include "cp_.h"


void cp_(char *source, char *destination) {
    struct stat src_stat, dest_stat;
    char newfile_name[BUFSIZE];
    char path[BUFSIZE];
    int is_dir = 0;

    // 원본 파일이 존재하는지 확인
    if (stat(source, &src_stat) < 0) {
        fprintf(stderr, "cp: cannot stat '%s': No such file or directory\n", source);
        return;
    }

    // destination 경로가 디렉토리인지 확인
    if (stat(destination, &dest_stat) == 0 && S_ISDIR(dest_stat.st_mode)) {
        is_dir = 1;
    }

    if (is_dir) {
        // 경로와 파일 이름 분리
        char *lastSlash = strrchr(destination, '/');
        if (lastSlash) {
            strncpy(path, destination, lastSlash - destination);
            path[lastSlash - destination] = '\0';
        } else {
            strcpy(path, destination);
        }

        // 새 파일 이름을 원본 파일 이름으로 설정
        strcpy(newfile_name, path);
        strcat(newfile_name, "/");
        strcat(newfile_name, strrchr(source, '/') + 1);

        // 파일 복사
        FILE *src, *dst;
        if ((src = fopen(source, "r")) == NULL) {
            fprintf(stderr, "cp: cannot open '%s' for reading: No such file or directory\n", source);
            return;
        }
        if ((dst = fopen(newfile_name, "w")) == NULL) {
            fclose(src);
            fprintf(stderr, "cp: cannot open '%s' for writing\n", newfile_name);
            return;
        }

        char buf[BUFSIZE];
        size_t n;
        while ((n = fread(buf, 1, BUFSIZE, src)) > 0) {
            if (fwrite(buf, 1, n, dst) != n) {
                fprintf(stderr, "cp: error writing to '%s'\n", newfile_name);
                break;
            }
        }

        fclose(src);
        fclose(dst);

    } else {
        // 파일 복사
        FILE *src, *dst;
        if ((src = fopen(source, "r")) == NULL) {
            fprintf(stderr, "cp: cannot open '%s' for reading: No such file or directory\n", source);
            return;
        }
        if ((dst = fopen(destination, "w")) == NULL) {
            fclose(src);
            fprintf(stderr, "cp: cannot open '%s' for writing\n", destination);
            return;
        }

        char buf[BUFSIZE];
        size_t n;
        while ((n = fread(buf, 1, BUFSIZE, src)) > 0) {
            if (fwrite(buf, 1, n, dst) != n) {
                fprintf(stderr, "cp: error writing to '%s'\n", destination);
                break;
            }
        }

        fclose(src);
        fclose(dst);
    }
}