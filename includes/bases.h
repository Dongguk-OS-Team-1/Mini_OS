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
# include <unistd.h> //chdir 함수를 사용하기 위해 포함해야 함
# include <ctype.h>


# define PATH_MAX   1024
# define NAME_MAX   1024
# define CMD_MAX    1024
# define PARSED_MAX 512
# define EXIT_CMD   "exit"
# define LS_CMD     "ls"
# define CD_CMD     "cd"
# define MKDIR_CMD  "mkdir"
# define CAT_CMD    "cat"
# define CHMOD_CMD  "chmod"
# define GREP_CMD   "grep"
# define CP_CMD     "cp"
# define TOUCH_CMD  "touch"
# define FIND_CMD   "find"
# define RMDIR_CMD  "rmdir"



int   find_cmd(int size, char **cmd);
int   parsing_cmd(char *target, char **ret);
void  make_lower_case_word(char *target);
void  init_1_dim_char(char *target, int size);
void  init_2_dim_char(char **target, int size);
void  clear_buffer(void);
int   is_absolute_path(const char *path);


#endif
