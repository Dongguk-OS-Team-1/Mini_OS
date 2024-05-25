#ifndef CHMOD_H
#define CHMOD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

mode_t convert_mode_str_to_oct(const char *mode_str);
int chmod_(int argc, char *argv[]);

#endif
