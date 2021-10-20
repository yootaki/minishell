/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heardoc_and_redirect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:41:50 by yootaki           #+#    #+#             */
/*   Updated: 2021/10/19 23:23:04 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin_cmd/builtin_cmd.h"
#include "../../includes/expansion.h"

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

void	proc_specified_fd(t_redirect *now)
{
	if (ft_isdigit(*(now->str)))
	{
		now->next->spec_flg = 1;
		now->next->spec_fd = ft_atoi(now->str);
	}
}

int	is_there_ctype(t_redirect *now)
{
	if (now->c_type == HEAR_DOC \
		|| now->c_type == T_LESSER \
		|| now->c_type == CHAR_LESSER \
		|| now->c_type == CHAR_GREATER \
		|| now->c_type == DGREATER)
	{
		return (1);
	}
	return (0);
}

int	validate_now_redirect_list(t_redirect *now)//int返してるの全部boolにした方がいいかも
{
	proc_specified_fd(now);
	if (!is_there_ctype(now))
		return (EXIT_FAILURE);
	now = now->next;
	if (check_redirect_syntax(now))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
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
		if (validate_now_redirect_list(now))
			return (EXIT_FAILURE);
		if (now->c_type == HEAR_DOC || now->c_type == T_LESSER)
		{
			now = now->next;
			if (hear_doc(now, env, now->str))
				return (EXIT_FAILURE);
		}
		else
		{
			now = now->next;
			if (redirect_file_open(now, env))
				return (EXIT_FAILURE);
		}
		now = now->next;
	}
	return (EXIT_SUCCESS);
}
