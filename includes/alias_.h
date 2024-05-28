/* ************************************************************************** */
/*                                                                            */
/*                                  alias_.h                                  */
/*                                                                            */
/*                       By: 최정흠 <andyc707@dgu.ac.kr>                      */
/*                                                                            */
/*                        Created: 2024/05/25 22:29:05                        */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALIAS_H
# define ALIAS_H

# include "bases.h"

# define MAX_ALIAS  1024
# define MAX_LINE   1024

typedef struct  s_alias {
    char alias[MAX_ALIAS];
    char command[MAX_ALIAS];
}               t_alias;

int is_command_only(char *target);
int add_alias(char *target);
int print_alias(void);

extern char alias_path[PATH_MAX];

#endif
