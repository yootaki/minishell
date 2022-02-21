/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 23:08:43 by yootaki           #+#    #+#             */
/*   Updated: 2022/02/21 15:15:59 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmd.h"
#include "expansion.h"

int	redirect_file_open(t_redirect *now, t_envlist *env)
{
	t_expanser	expanser;
	char		*filename;

	init_expanser(&expanser, now->str);
	expansionvar_and_deletequote(&expanser, env);
	filename = expanser.str;
	if (!ft_strncmp(now->prev->str, "<", ft_strlen("<") + 1))
		now->redirect_fd = open(filename, O_RDWR);
	else if (!ft_strncmp(now->prev->str, ">", ft_strlen(">") + 1))
		now->redirect_fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, S_IRWXU);
	else if (!ft_strncmp(now->prev->str, ">>", ft_strlen(">>") + 1))
		now->redirect_fd = open(filename, O_CREAT | O_APPEND | O_RDWR, S_IRWXU);
	else
		printf("parse error near `>'\n");
	free(expanser.str);
	if (now->redirect_fd == -1)
		return (print_error_func("open"));
	return (EXIT_SUCCESS);
}
