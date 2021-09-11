/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 23:08:43 by yootaki           #+#    #+#             */
/*   Updated: 2021/09/11 17:31:54 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin_cmd/builtin_cmd.h"
#include "../../includes/expansion.h"

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
	if (now->redirect_fd == -1)
		return (print_error_func("open"));
	free(filename);
	return (EXIT_SUCCESS);
}
