#include "bases.h"
#include "touch_.h"

//-a 옵션을 통해 접근 시간(atime)을 현재 시간으로 변경
//-m 옵션을 사용해서 수정 시간(mtime)을 현재 시간으로 변경하는 기능과  touch로 시간만 변경
//-a와 -m 옵션 사용시 Change 타임도 함께 변경된다.
//-c 옵션을 사용해서 파일을 생성하지 않는 기능 추가

//추가적으로 구현할 사항이 있다면 
//현재 birth 시간이 표시가 안되는데 이 부분 추가 or -d 옵션: 변경할 시간 지정 기능 추가 가능

// Helper function to parse options
void parse_options(int argc, char **argv, bool *opt_a, bool *opt_m, bool *opt_c, int *idx) {
    *opt_a = false;
    *opt_m = false;
    *opt_c = false;
    *idx = 1;

    while (*idx < argc && argv[*idx][0] == '-') {
        for (int j = 1; argv[*idx][j] != '\0'; j++) {
            if (argv[*idx][j] == 'a') *opt_a = true;
            else if (argv[*idx][j] == 'm') *opt_m = true;
            else if (argv[*idx][j] == 'c') *opt_c = true;
            else {
                fprintf(stderr, "unknown option -- '%c'\n", argv[*idx][j]);
                exit(1);
            }
        }
        (*idx)++;
    }
}


void touch_(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s [-amc] <file1> <file2> ...\n", argv[0]);
        exit(1);
    }

    bool opt_a, opt_m, opt_c;
    int idx;
    parse_options(argc, argv, &opt_a, &opt_m, &opt_c, &idx);

    for (int i = idx; i < argc; i++) {
        char *filename = argv[i];
        struct stat st;
        struct utimbuf new_times;

        // Check if the file exists
        if (stat(filename, &st) < 0) {
            if (opt_c) continue; // -c option: don't create the file
            int fd = creat(filename, 0664);
            if (fd < 0) {
                fprintf(stderr, "file create error for %s\n", filename);
                exit(1);
            }
            close(fd);
            // Set new file times if created
            new_times.actime = time(NULL);
            new_times.modtime = time(NULL);
            if (utime(filename, &new_times) < 0) {
                fprintf(stderr, "utime error for %s\n", filename);
                exit(1);
            }
        } else {
            if (opt_a && opt_m) {
                new_times.actime = time(NULL); // set atime to current time
                new_times.modtime = time(NULL); // set mtime to current time
            } else if (opt_a) {
                new_times.actime = time(NULL); // set atime to current time
                new_times.modtime = st.st_mtime; // keep the original mtime
            } else if (opt_m) {
                new_times.actime = st.st_atime; // keep the original atime
                new_times.modtime = time(NULL); // set mtime to current time
            } else {
                new_times.actime = time(NULL); // set both atime and mtime to current time
                new_times.modtime = time(NULL);
            }

            if (utime(filename, &new_times) < 0) {
                fprintf(stderr, "utime error for %s\n", filename);
                exit(1);
            }
        }
    }
}