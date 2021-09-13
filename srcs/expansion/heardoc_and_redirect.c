/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heardoc_and_redirect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:41:50 by yootaki           #+#    #+#             */
/*   Updated: 2021/09/07 14:25:46 by yootaki          ###   ########.fr       */
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
		if (!ft_strncmp(now->str, "<<", ft_strlen(now->str)))
		{
			now = now->next;
			if (now->str == NULL)
				printf("bash: syntax error near unexpected token `newline'\n");
			hear_doc(now, env, now->str);
		}
		if (!ft_strncmp(now->str, ">", ft_strlen(now->str)) \
		|| !ft_strncmp(now->str, ">>", ft_strlen(now->str)))
		{
			now = now->next;
			if (now->str == NULL)
				printf("bash: syntax error near unexpected token `newline'\n");
			redirect_file_open(now, env);
		}
		now = now->next;
	}
	return (EXIT_SUCCESS);
}
