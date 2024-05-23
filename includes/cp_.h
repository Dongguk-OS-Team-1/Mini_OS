/* ************************************************************************** */
/*                                                                            */
/*                                    cp_.h                                   */
/*                                                                            */
/*                              By: 신민철                                    */
/*                                                                            */
/*                        Created: 2024/05/22                                 */
/*                                                                            */
/* ************************************************************************** */


#ifndef CP_H
# define CP_H


# include <stdlib.h>
# include <unistd.h> //chdir 함수를 사용하기 위해 포함해야 함
# include <fcntl.h>
# include <errno.h>
# include <sys/syscall.h>
# include <sys/fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>

#define BUFSIZE 4096

#endif