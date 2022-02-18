/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:43:01 by yootaki           #+#    #+#             */
/*   Updated: 2022/02/03 20:00:23y yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmd.h"

#define VALID_IDENTIFIER "minishell: unset: `': not a valid identifier\n"

int	delete_key_and_value(char *unset_obj, t_envlist *envp_lst)
{
	t_envlist	*tmp;
	char		*env_key;
	int			char_cnt;

	char_cnt = 0;
	while (unset_obj[char_cnt] != '=' && unset_obj[char_cnt])
		char_cnt++;
	env_key = malloc_and_strlcpy(unset_obj, ++char_cnt);
	tmp = envp_lst->next;
	while (tmp != envp_lst && ft_strncmp(tmp->key, env_key, char_cnt))
		tmp = tmp->next;
	if (tmp == envp_lst)
		return (g_status);
	free(tmp->key);
	free(tmp->value);
	ft_envlstdelone(tmp);
	free(env_key);
	return (g_status);
}

bool	validate_unset_obj(char *obj)
{
	if (obj == NULL)
	{
		return (false);
	}
	else if (obj[0] == ' ')
	{
		return (false);
	}
	while (*obj != '\0')
	{
		if (ft_isdigit(*obj))
			return (false);
		obj++;
	}
	return (true);
}

int	my_unset(t_cmd_lst *cmd, t_envlist *envp_lst)
{
	t_cmd_lst	*now;
	char		*unset_obj;

	now = cmd->next->next;
	g_status = 0;
	if (now == cmd)
		return (g_status);
	while (now != cmd)
	{
		unset_obj = now->str;
		if (validate_unset_obj(unset_obj) == false)
		{
			ft_putstr_fd(VALID_IDENTIFIER, STDERR_FILENO);
			g_status = 1;
			now = now->next;
			continue ;
		}
		if (delete_key_and_value(unset_obj, envp_lst))
			return (g_status);
		now = now->next;
	}
	return (g_status);
}
