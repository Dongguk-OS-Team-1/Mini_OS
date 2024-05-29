/* ************************************************************************** */
/*                                                                            */
/*                                   rmdir_.h                                 */
/*                                                                            */
/*                       By: 최정흠 <andyc707@dgu.ac.kr>                      */
/*                                                                            */
/*                        Created: 2024/05/20 15:15:33                        */
/*                                                                            */
/* ************************************************************************** */

#ifndef RMDIR_H
# define RMDIR_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/fcntl.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/syscall.h>
# include <pthread.h>

# define MAX 1024

typedef struct  s_thread_args {
    char    dir_name[MAX];
}               ThreadArgs;

int find_brace_pattern(char *target, int *start, int *end);

extern char log_path[PATH_MAX];

#endif
