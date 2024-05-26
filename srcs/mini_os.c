/* ************************************************************************** */
/*                                                                            */
/*                                  mini_os.c                                 */
/*                                                                            */
/*                       By: 최정흠 <andyc707@dgu.ac.kr>                      */
/*                                                                            */
/*                        Created: 2024/05/10 21:20:02                        */
/*                                                                            */
/* ************************************************************************** */

#include "bases.h"
#include "commands.h"

int main(void) {
    int parsed_cnt;
    int is_user_exit;
    char current_dir[PATH_MAX];
    char input_cmd[CMD_MAX];
    char *parsed_cmd[PARSED_MAX];

    is_user_exit = 0;
    while (1) {
        init_1_dim_char(input_cmd, CMD_MAX);
        init_2_dim_char(parsed_cmd, PARSED_MAX);
        getcwd(current_dir, PATH_MAX);
        printf("%s > ", current_dir);
        fgets(input_cmd, sizeof(input_cmd), stdin);
        parsed_cnt = parsing_cmd(input_cmd, parsed_cmd);

        // if user input is ENTER
        if (parsed_cnt < 1)
            continue;

        make_lower_case_word(parsed_cmd[0]);
        is_user_exit = find_cmd(parsed_cnt, parsed_cmd);
        if (is_user_exit)
            break;
    }

    return (0);
}
