/* ************************************************************************** */
/*                                                                            */
/*                                dir_bases.c                                 */
/*                                                                            */
/*                       By: 최정흠 <andyc707@dgu.ac.kr>                      */
/*                                                                            */
/*                        Created: 2024/05/14 16:29:12                        */
/*                                                                            */
/* ************************************************************************** */

#include "dir_bases.h"

int find_brace_pattern(char *target, int *start, int *end) {

    char temp[MAX];
    // Parsing from "abc{1..3}" for get baseName, start, end
    if (sscanf(target, "%1023[^{]{%d..%d}", temp, start, end) == 3 && target[strlen(target) - 1] == '}')
        return (1);
    else
        return (0);
}
