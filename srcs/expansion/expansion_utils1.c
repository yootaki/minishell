/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:56:56 by yootaki           #+#    #+#             */
/*   Updated: 2021/10/18 17:44:49 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin_cmd/builtin_cmd.h"
#include "../../includes/expansion.h"

int	init_expanser(t_expanser *expanser, char *str)
{
	expanser->str = ft_strdup(str);
	if (expanser->str == NULL)
		return (EXIT_FAILURE);
	expanser->str_cnt = 0;
	expanser->dquote_flag = 0;
	expanser->quote_flag = 0;
	return (EXIT_SUCCESS);
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

char	*strjoin_minishell(char *str1, char *str2)
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
