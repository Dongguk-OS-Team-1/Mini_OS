/* ************************************************************************** */
/*                                                                            */
/*                                  commands.h                                */
/*                                                                            */
/*                       By: 최정흠 <andyc707@dgu.ac.kr>                      */
/*                                                                            */
/*                        Created: 2024/05/14 16:19:02                        */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H

# define COMMANDS_H



void mkdir_(int argc, char *argv[]);
int grep_(int argc, char *argv[]);
int chmod_(int argc, char *argv[]);
void cp_(char *source, char *destination);
void touch_(int argc, char ** argv);
void find_(int argc, char *argv[]);

void cd_(int argc, char* argv[]);
void  cat_(int argc, char* argv[]);

void list_directory(int argc, char **argv);



#endif