/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:56:56 by yootaki           #+#    #+#             */
/*   Updated: 2021/11/05 13:40:14 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmd.h"
#include "expansion.h"

char	*get_var_name(char *str)
{
	char	*var_name;
	int		name_len;

	name_len = 0;
	if (str[name_len] == '?')
		name_len++;
	else
	{
		while (str[name_len] != '\0' \
		&& (ft_isalnum(str[name_len]) || str[name_len] == '_'))
			name_len++;
	}
	var_name = (char *)malloc(sizeof(char) * (++name_len));
	if (!var_name)
		exit (print_error_func("malloc"));
	ft_strlcpy(var_name, str, name_len);
	return (var_name);
}

char	*get_var_value(char *str, t_envlist *env)
{
	t_envlist	*now;
	char		*var_value;

	if (*str == '?')
		return (ft_xitoa(g_status));
	now = env->next;
	while (now != env)
	{
		if (!ft_strncmp(now->key, str, ft_strlen(str) + 1))
		{
			var_value = ft_xstrdup(now->value);
			if (!var_value)
				exit (EXIT_FAILURE);
			return (var_value);
		}
		now = now->next;
	}
	return (NULL);
}

int	change_underbar(t_nlst *now, t_envlist *envp_lst)
{
	t_envlist	*tmp;

	tmp = envp_lst->next;
	while (tmp != envp_lst)
	{
		if (!ft_strncmp(tmp->key, "_", 2))
		{
			free(tmp->value);
			if (now->cmd->prev->str == NULL)
				tmp->value = ft_xstrdup("");
			else
				tmp->value = ft_xstrdup(now->cmd->prev->str);
			if (!tmp->value)
				exit (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		tmp = tmp->next;
	}
	return (EXIT_FAILURE);
}

bool	is_var_name(int c)
{
	if (ft_isalnum(c) || ft_isdigit(c) || c == '_' || c == '?')
		return (true);
	else
		return (false);
}
