/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:56:56 by yootaki           #+#    #+#             */
/*   Updated: 2021/09/13 15:47:23 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin_cmd/builtin_cmd.h"
#include "../../includes/expansion.h"

void	init_expanser(t_expanser *expanser, char *str)
{
	expanser->str = str;
	expanser->str_cnt = 0;
	expanser->dquote_flag = 0;
	expanser->quote_flag = 0;
}

char	*get_var_name(char *str)
{
	char	*var_name;
	int		name_len;

	name_len = 0;
	while (str[name_len] != '\0' \
	&& str[name_len] != '$' && str[name_len] != ' ' \
	&& str[name_len] != '\"' && str[name_len] != '\'' \
	&& !((str[name_len] >= 'a') && (str[name_len] <= 'z')))
		name_len++;
	var_name = (char *)malloc(sizeof(char) * (++name_len));
	ft_strlcpy(var_name, str, name_len);
	return (var_name);
}

char	*get_var_value(char *str, t_envlist *env)
{
	t_envlist	*now;

	now = env->next;
	while (now != env)
	{
		if (!ft_strncmp(now->key, str, ft_strlen(str)))
			return (now->value);
		now = now->next;
	}
	return (NULL);
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
