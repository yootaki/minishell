/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:56:56 by yootaki           #+#    #+#             */
/*   Updated: 2021/10/02 13:51:23 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin_cmd/builtin_cmd.h"
#include "../../includes/expansion.h"

char	*get_var_name(char *str)
{
	char	*var_name;
	int		name_len;

	name_len = 0;
	while (str[name_len] != '\0' \
	&& str[name_len] != '$' && str[name_len] != ' ' \
	&& str[name_len] != '\"' && str[name_len] != '\'' \
	&& str[name_len] != '.' \
	&& !(((str[name_len] >= 'a') && (str[name_len] <= 'z')) || ft_isdigit(str[name_len])))
		name_len++;
	var_name = (char *)malloc(sizeof(char) * (++name_len));
	ft_strlcpy(var_name, str, name_len);
	return (var_name);
}

char	*get_var_value(char *str, t_envlist *env)
{
	t_envlist	*now;

	if (*str == '?')
		return (ft_itoa(g_status));
	now = env->next;
	while (now != env)
	{
		if (!ft_strncmp(now->key, str, ft_strlen(str) + 1))
			return (ft_strdup(now->value));
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
				tmp->value = ft_strdup("");
			else
				tmp->value = ft_strdup(now->cmd->prev->str);
			if (tmp->value == NULL)
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		tmp = tmp->next;
	}
	return (EXIT_FAILURE);
}

/* この判定関数は別の部分でも使用する */
/* 変数名に使用可能な文字以外がきたら0を返す(false) */
int	is_var_name(int c)
{
	if (ft_isalnum(c) || ft_isdigit(c) || c == '_' || c == '?')
		return (1);
	else
		return (0);
}
