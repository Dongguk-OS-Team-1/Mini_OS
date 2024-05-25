#ifndef GREP_H
#define GREP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
void to_lowercase(char *str);
void grep_impl(const char *pattern, const char *file_path, int options);
int grep_(int argc, char *argv[]);

#endif
