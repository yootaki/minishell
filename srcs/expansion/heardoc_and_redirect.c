/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heardoc_and_redirect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:41:50 by yootaki           #+#    #+#             */
/*   Updated: 2021/10/10 20:07:47 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin_cmd/builtin_cmd.h"
#include "../../includes/expansion.h"

#define ERR_SYNTAX "minishell: syntax error near unexpected token `"
#define ERR_SYNTAX_NULL "newline'\n"
#define ERR_SYNTAX_FILEIN "<'\n"
#define ERR_SYNTAX_FILEOUT ">'\n"
#define ERR_SYNTAX_FILEAPPEND ">>'\n"
#define ERR_SYNTAX_PIPE "|'\n"

int	print_error_func(char *err_func)
{
	perror(err_func);
	return (EXIT_FAILURE);
}

void	print_syntax_error(char *str)
{
	ft_putstr_fd(ERR_SYNTAX, STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	g_status = 258;
}

int	check_redirect_syntax(t_redirect *now)
{
	if (now->str == NULL)
		print_syntax_error(ERR_SYNTAX_NULL);
	else if (now->c_type == T_LESSER)
		return (EXIT_SUCCESS);
	else if (*(now->str) == '<' && *(now->str + 1) == '<')
		print_syntax_error(ERR_SYNTAX_FILEIN);
	else if (*(now->str) == '<')
		print_syntax_error(ERR_SYNTAX_FILEIN);
	else if (*(now->str) == '>' && *(now->str + 1) == '>')
		print_syntax_error(ERR_SYNTAX_FILEAPPEND);
	else if (*(now->str) == '>')
		print_syntax_error(ERR_SYNTAX_FILEOUT);
	else if (*(now->str) == '|')
		print_syntax_error(ERR_SYNTAX_PIPE);
	else
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

//expanded_lineがmallocしてる
int	heardoc_and_redirect(t_redirect *redirect, t_envlist *env)
{
	t_redirect	*now;

	now = redirect->next;
	if (now->str == NULL)
		return (EXIT_SUCCESS);
	while (now != redirect)
	{
		if (ft_isdigit(*(now->str)))
		{
			now->next->spec_flg = 1;
			now->next->spec_fd = ft_atoi(now->str);
		}
		if (now->c_type == HEAR_DOC || now->c_type == T_LESSER)
		{
			now = now->next;
			if (check_redirect_syntax(now))
				return (EXIT_FAILURE);
			if (hear_doc(now, env, now->str))
				return (EXIT_FAILURE);
		}
		else if (now->c_type == CHAR_LESSER \
		|| now->c_type == CHAR_GREATER \
		|| now->c_type == DGREATER)
		{
			now = now->next;
			if (check_redirect_syntax(now))
				return (EXIT_FAILURE);
			if (redirect_file_open(now, env))
				return (EXIT_FAILURE);
		}
		now = now->next;
	}
	return (EXIT_SUCCESS);
}
