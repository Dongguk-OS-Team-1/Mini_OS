/* ************************************************************************** */
/*                                                                            */
/*                                  find_.h                                   */
/*                                                                            */
/*                       By: 최정흠 <andyc707@dgu.ac.kr>                      */
/*                                                                            */
/*                        Created: 2024/05/19 18:16:25                        */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIND_H
# define FIND_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <dirent.h>

void find_files(const char *path);
void name_recur(char *name, char *target);
void type_recur(char *name, char *mode);
int is_absolute_path(const char *path);

#endif
