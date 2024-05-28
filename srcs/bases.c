/* ************************************************************************** */
/*                                                                            */
/*                                  bases.c                                   */
/*                                                                            */
/*                       By: 최정흠 <andyc707@dgu.ac.kr>                      */
/*                                                                            */
/*                        Created: 2024/05/12 14:40:02                        */
/*                                                                            */
/* ************************************************************************** */

#include "bases.h"
#include "commands.h"

int find_cmd(int size, char **cmd) {

    int is_user_exit;

    is_user_exit = 0;
    if (strcmp(cmd[0], LS_CMD) == 0) {
        list_directory(size, cmd);
    } else if (strcmp(cmd[0], CD_CMD) == 0) {
        cd_(size, cmd);
    } else if (strcmp(cmd[0], MKDIR_CMD) == 0) {
        mkdir_(size, cmd);
    } else if (strcmp(cmd[0], RMDIR_CMD) == 0) {
        rmdir_(size, cmd);
    } else if (strcmp(cmd[0], CAT_CMD) == 0) {
        cat_(size, cmd);
    } else if (strcmp(cmd[0], CHMOD_CMD) == 0) {
        chmod_(size, cmd);
    } else if (strcmp(cmd[0], GREP_CMD) == 0) {
        grep_(size, cmd);
    } else if (strcmp(cmd[0], CP_CMD) == 0) {
        if (size == 3)
            cp_(cmd[1], cmd[2]);
        else
            fprintf(stderr, "cp: missing file operand\n");
    } else if (strcmp(cmd[0], TOUCH_CMD) == 0) {
        touch_(size, cmd);
    } else if (strcmp(cmd[0], FIND_CMD) == 0) {
        find_(size, cmd);
    } else if (strcmp(cmd[0], ALIAS_CMD) == 0) {
        printf("alias input\n");
        alias_(size, cmd);
    } else if (strcmp(cmd[0], EXIT_CMD) == 0) {
        is_user_exit = 1;
    } else
        printf("bash: command not found: %s\n", cmd[0]);

    return (is_user_exit);
}

int parsing_cmd(char *target, char **ret) {
    int cnt;
    char *token;
    char *temp;

    cnt = 0;
    temp = target;
    while ((token = strtok_r(temp, " \n", &temp))) {
        if (cnt >= PARSED_MAX)
            break;
        ret[cnt] = token;
        cnt++;
    }

    return (cnt);
}

void make_lower_case_word(char *target) {
    while (*target) {
        *target = tolower((unsigned char) *target);
        target++;
    }

    return ;
}

int init_log_alias_path(void) {

    if (chdir("./resources") != 0) {
        fprintf(stderr, "ERROR : Not Found resources directory.\n");
        return (0);
    }

    getcwd(alias_path, sizeof(alias_path));
    strncat(alias_path, ALIAS_FILE, sizeof(ALIAS_FILE));

    getcwd(log_path, sizeof(log_path));
    strncat(log_path, LOG_FILE, sizeof(LOG_FILE));

    if (chdir("../") != 0) {
         fprintf(stderr, "ERROR : Can not change directory.\n");
        return (0);
    }

    return (1);
}

void init_1_dim_char(char *target, int size) {
    for (int i = 0; i < size; i++)
        *(target + i) = 0;

    return ;
}

void init_2_dim_char(char **target, int size) {

    for (int i = 0; i < size; i++)
        *(target + i) = 0;

    return ;
}

void clear_buffer(void) {

    while (getchar() != '\n');

    return ;
}

int is_absolute_path(const char *path) {
    return (path[0] == '/');
}
