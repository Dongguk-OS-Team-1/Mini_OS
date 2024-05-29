/* ************************************************************************** */
/*                                                                            */
/*                                  alias_.c                                  */
/*                                                                            */
/*                       By: 최정흠 <andyc707@dgu.ac.kr>                      */
/*                                                                            */
/*                        Created: 2024/05/25 22:28:39                        */
/*                                                                            */
/* ************************************************************************** */

#include "alias_.h"

void alias_(int argc, char *argv[]) {

    if (argc == 1) {
        print_alias();
        return ;
    }

    if (argc != 2) {
        fprintf(stderr, "alias : Invalid arguments.\n");
        return ;
    }

    add_alias(*(argv + 1));

    return ;
}

void get_alias_command(char *target) {

    FILE    *alias_file;
    int     is_alias;
    char    line[MAX_LINE];
    char    temp_target[MAX_LINE];
    char    *temp;
    char    *temp_strtok;
    t_alias temp_alias;

    if (target == NULL || *target == '\0')
        return ;

    if ((alias_file = fopen(alias_path, "r")) == NULL) {
        fprintf(stderr, "alias: %s: file open failed.\n", alias_path);
        return ;
    }

    strcpy(temp_target, target);
    strtok(target, " ");
    is_alias = 0;
    while (fgets(line, sizeof(line), alias_file)) {
        if (strcmp(line, "\n") == 0)
            break ;

        temp = strtok(line, "=");
        strcpy(temp_alias.alias, temp);

        temp = strtok(NULL, "\n");
        strcpy(temp_alias.command, temp);

        if (strcmp(temp_alias.alias, target) == 0) {
            temp = strtok(temp_alias.command, "\'");
            if (is_command_only(temp)) {
                strtok(temp_target, " ");
                strcat(temp, " ");
                temp_strtok = strtok(NULL, "");
                temp_strtok = temp_strtok ? temp_strtok : "";
                strcat(temp, temp_strtok);
            }

            strcpy(target, temp);
            is_alias = 1;
            break ;
        }
    }

    if (!is_alias)
        strcpy(target, temp_target);

    fclose(alias_file);

    return ;
}

int is_command_only(char *target) {
    
    if (strcmp(target, EXIT_CMD) == 0)
        return (1);
    else if (strcmp(target, LS_CMD) == 0)
        return (1);
    else if (strcmp(target, CD_CMD) == 0)
        return (1);
    else if (strcmp(target, MKDIR_CMD) == 0)
        return (1);
    else if (strcmp(target, CAT_CMD) == 0)
        return (1);
    else if (strcmp(target, CHMOD_CMD) == 0)
        return (1);
    else if (strcmp(target, GREP_CMD) == 0)
        return (1);
    else if (strcmp(target, CP_CMD) == 0)
        return (1);
    else if (strcmp(target, TOUCH_CMD) == 0)
        return (1);
    else if (strcmp(target, FIND_CMD) == 0)
        return (1);
    else if (strcmp(target, RMDIR_CMD) == 0)
        return (1);
    else if (strcmp(target, ALIAS_CMD) == 0)
        return (1);
    return (0);
}

int add_alias(char *target) {

    FILE  *alias_file;

    if ((alias_file = fopen(alias_path, "a")) == NULL) {
        fprintf(stderr, "alias: %s: file open failed.\n", alias_path);
        return (0);
    }

    fprintf(alias_file, "%s\n", target);

    fclose(alias_file);

    return (1);
}

int print_alias(void) {

    FILE  *alias_file;
    char  line[MAX_LINE];

    if ((alias_file = fopen(alias_path, "r")) == NULL) {
        fprintf(stderr, "alias: %s: file open failed.\n", alias_path);
        return (0);
    }

    while (fgets(line, sizeof(line), alias_file))
        printf("%s", line);
    printf("\n");
    fclose(alias_file);

    return (1);
}
