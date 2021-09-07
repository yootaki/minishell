#ifndef EXPANSION_H
# define EXPANSION_H

# include "../get_next_line/get_next_line.h"
# include "../srcs/builtin_cmd/builtin_cmd.h"
# include "input.h"
# include "parse.h"
# include "utils.h"
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
	int		dquote_flag;
	int		quote_flag;
}t_expanser;

enum
{
	ISSTR,
	ISFILE,
	ISDIRECTORY
};

/* expansion */
void	init_expanser(t_expanser *expanser, char *str);
void	quotation_flag_check(t_expanser *expanser);
int		expansionvar_and_deletequote(t_expanser *expanser, t_envlist *env);
void	expansion_var(t_expanser *expanser, t_envlist *env);
int		expanser(t_cmd_lst *cmd, t_envlist *env);

/* expansion_utils */
char	*get_var_name(char *str);
char	*get_var_value(char *str, t_envlist *env);
int		categorize(t_cmd_lst *now);

/* heardoc.c */
int	hear_doc(t_redirect *now, t_envlist *env, char *separator);

/* redirect */
int	redirect_file_open(t_redirect *now, t_envlist *env);

/* heardoc_and_redirect */
char	*heardoc_expansion_var(char *line, t_envlist *env);
int		print_error_func(char *err_func);
int		heardoc_and_redirect(t_redirect *redirect, t_envlist *env);


/* delete_quote */
void	delete_dquote(t_expanser *expanser);
void	delete_quote(t_expanser *expanser);

/* sepalate_str */
int	sep_str(t_cmd_lst *now, t_expanser *expanser);

#endif
