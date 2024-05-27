#ifndef CHMOD_H
#define CHMOD_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
void print_usage(char *program_name);
mode_t parse_symbolic_mode(char *mode_str);
mode_t parse_numeric_mode(char *mode_str);
int chmod_(int argc, char *argv[]);

#endif
