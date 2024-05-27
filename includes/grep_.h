#ifndef GREP_H
#define GREP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
void grep_impl(const char *pattern, const char *file_path, bool ignore_case, bool invert_match, bool show_line_numbers);
int grep_(int argc, char *argv[]);

#endif
