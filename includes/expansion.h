/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:05:52 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/21 14:40:11 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "../get_next_line/get_next_line.h"
# include "../srcs/builtin_cmd/builtin_cmd.h"
# include "input.h"
# include "parse.h"
# include "utils.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# define ERR_SYNTAX "minishell: syntax error near unexpected token `"
# define ERR_SYNTAX_NULL "newline'\n"
# define ERR_SYNTAX_FILEIN "<'\n"
# define ERR_SYNTAX_FILEOUT ">'\n"
# define ERR_SYNTAX_FILEAPPEND ">>'\n"
# define ERR_SYNTAX_PIPE "|'\n"

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

typedef enum e_flag
{
	SKIP,
	FAILURE,
	SUCCESS
}	t_flag;

t_token_type	check_cmd_exist(char *line);

/* expansion */
void			quotation_flag_check(t_expanser *expanser);
int				expansionvar_and_deletequote(t_expanser \
*expanser, t_envlist *env);
void			expansion_var(t_expanser *expanser, t_envlist *env);
int				expanser(t_cmd_lst *cmd, t_envlist *env);
int				expansion(t_nlst *node, t_envlist *envp_lst);

/* expansion_utils1 */
int				print_error_func(char *err_func);
void			print_syntax_error(char *str);
void			init_expanser(t_expanser *expanser, char *str);
int				categorize(t_cmd_lst *now);
char			*strjoin_minishell(char *str1, char *str2);

/* expansion_utils2 */
char			*get_var_value(char *str, t_envlist *env);
char			*get_var_name(char *str);
bool			is_var_name(int c);
int				change_underbar(t_nlst *now, t_envlist *envp_lst);

/* heardoc.c */
int				hear_doc(t_redirect *now, t_envlist *env, char *separator);

/* redirect */
int				redirect_file_open(t_redirect *now, t_envlist *env);

/* heardoc_and_redirect */
char			*heardoc_expansion_var(char *line, t_envlist *env);
int				print_error_func(char *err_func);
int				heardoc_and_redirect(t_redirect *redirect, t_envlist *env);

/* delete_quote */
void			delete_quotation_mark(t_expanser *expanser, char mark);

/* separate_str */
int				put_separated_expanser_to_now(t_cmd_lst *now, \
											t_expanser *expanser, \
											int *count);

t_flag			pipe_next_cmd_check(t_nlst \
*node, t_envlist *envp_lst, t_nlst *n_lst);
char			*xstrjoin(char *s1, char const *s2);
void			nlst_bottom_add(t_nlst *old_node, t_nlst *new_node);
void			delete_node(t_nlst *node, t_nlst *now_node);

void			xcheck(t_nlst *nil);
t_nlst			*xget_cmdline_from_input_str(char \
*command, t_envlist *envp_lst);
int				add_new_node_lst(t_nlst \
*n_lst, t_envlist *envp_lst, char *p_line);
int				cmd_cmb(char **p_line, char *line);
int				add_pipe_next_cmd(char **p_line);
t_flag			pipe_next_cmd_check(t_nlst \
*node, t_envlist *envp_lst, t_nlst *n_lst);

#endif
