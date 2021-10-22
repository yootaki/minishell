/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:56:56 by yootaki           #+#    #+#             */
/*   Updated: 2021/10/22 17:57:13 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin_cmd/builtin_cmd.h"
#include "../../includes/expansion.h"

int	print_error_func(char *err_func)
{
	perror(err_func);
	g_status = 1;
	return (EXIT_FAILURE);
}

void	print_syntax_error(char *str)
{
	ft_putstr_fd(ERR_SYNTAX, STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	g_status = 258;
}

void	init_expanser(t_expanser *expanser, char *str)
{
	expanser->str = ft_strdup(str);
	if (expanser->str == NULL)//malloc
		exit (print_error_func("malloc"));
	expanser->str_cnt = 0;
	expanser->dquote_flag = 0;
	expanser->quote_flag = 0;
}

int	categorize(t_cmd_lst *now)
{
	struct stat		buf;

	if (stat(now->str, &buf))
		return (ISSTR);
	if (S_ISREG(buf.st_mode))
		return (ISFILE);
	else if (S_ISDIR(buf.st_mode))
		return (ISDIRECTORY);
	return (ISSTR);
}

char	*strjoin_minishell(char *str1, char *str2)//malloc
{
	if (str1 == NULL && str2 == NULL)
		return (NULL);
	else if (str1 == NULL)
		return (str2);
	else if (str2 == NULL)
		return (str1);
	else
		return (ft_strjoin(str1, str2));
}
