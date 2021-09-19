/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heardoc_and_redirect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:41:50 by yootaki           #+#    #+#             */
/*   Updated: 2021/09/16 16:02:05 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin_cmd/builtin_cmd.h"
#include "../../includes/expansion.h"

int	print_error_func(char *err_func)
{
	perror(err_func);
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
		if (!ft_strncmp(now->str, "<<", ft_strlen("<<") + 1))
		{
			now = now->next;
			if (now->str == NULL)
				printf("bash: syntax error near unexpected token `newline'\n");
			hear_doc(now, env, now->str);
		}
		if (!ft_strncmp(now->str, "<", ft_strlen("<") + 1) \
		|| !ft_strncmp(now->str, ">", ft_strlen(">") + 1) \
		|| !ft_strncmp(now->str, ">>", ft_strlen(">>") + 1))
		{
			now = now->next;
			if (now->str == NULL)
			{
				printf("bash: syntax error near unexpected token `newline'\n");
				return (EXIT_FAILURE);
			}
			else if (*(now->str) == '<' || *(now->str) == '>')
			{
				write(STDERR_FILENO, "bash: syntax error near unexpected token `>'\n", ft_strlen("bash: syntax error near unexpected token `>'\n"));
				//ここはexitするのが正解？returnが正解？
				exit (2);
			}
			redirect_file_open(now, env);
		}
		now = now->next;
	}
	return (EXIT_SUCCESS);
}
