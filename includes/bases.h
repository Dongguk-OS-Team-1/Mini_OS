/* ************************************************************************** */
/*                                                                            */
/*                                  bases.h                                   */
/*                                                                            */
/*                       By: 최정흠 <andyc707@dgu.ac.kr>                      */
/*                                                                            */
/*                        Created: 2024/05/10 21:19:32                        */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASES_H
# define BASES_H

# include <stdio.h>
# include <string.h>
# include <ctype.h>

# define CMD_MAX        256
# define PARSED_MAX     64
# define EXIT_CMD       "exit"
# define LS_CMD         "ls"
# define CD_CMD         "cd"
# define MKDIR_CMD      "mkdir"
# define CAT_CMD        "cat"
# define CHMOD_CMD      "chmod"
# define GREP_CMD       "grep"
# define CP_CMD         "cp"
# define TOUCH_CMD      "touch"
# define OWNER_MAX      128
# define GROUP_MAX      128
# define NAME_NODE_MAX  128
# define NODE_MAX       128

int   find_cmd(char **cmd, int size);
int   parsing_cmd(char *target, char **ret);
void  make_lower_case_word(char *target);
void  init_1_dim_char(char *target, int size);
void  init_2_dim_char(char **target, int size);
void  clear_buffer(void);

typedef struct  s_time {
    short month;
    short day;
    short hour;
    short minute;
}               t_time;

typedef struct  s_node {
    int           type;
    int           link_cnt;
    char          owner[OWNER_MAX];
    char          group[GROUP_MAX];
    unsigned long size;
    t_time        v_time;
    char          name[NAME_NODE_MAX];
    struct s_node *a_node;
}               t_node;

#endif
