/* ************************************************************************** */
/*                                                                            */
/*                                    mkdir.h                                 */
/*                                                                            */
/*                       By: 최정흠 <andyc707@dgu.ac.kr>                      */
/*                                                                            */
/*                        Created: 2024/05/14 17:18:53                        */
/*                                                                            */
/* ************************************************************************** */

#ifndef MKDIR_H
# define MKDIR_H

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
    int     dirfd;
    char    dir_name[MAX];
    mode_t  mode;
}               ThreadArgs;

#endif
