#ifndef EXPANSION_H
# define EXPANSION_H

# include "../get_next_line/get_next_line.h"
# include "input.h"
# include "parse.h"
# include "utils.h"
# include "../srcs/builtin_cmd/builtin_cmd.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_expanser
{
	char	*str;
	int		str_cnt;
}t_expanser;

enum
{
	ISSTR,
	ISFILE,
	ISDIRECTORY
};

/* expansion.c */
char	*get_var_name(char *str);
char	*get_var_value(char *str, t_envlist *env);
int	expanser(t_cmd_lst *cmd, t_envlist *env);

/* here_doc.c */
int	heardoc_and_redirect(t_redirect *redirect, t_envlist *env);

/* delete_quote */
void	delete_dquote(t_expanser *expanser);
void	delete_quote(t_expanser *expanser);

/* sepalate_str */
int		sep_str(t_cmd_lst *now, t_expanser *expanser);

#endif
