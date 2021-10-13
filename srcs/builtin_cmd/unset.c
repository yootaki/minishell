/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:43:01 by yootaki           #+#    #+#             */
/*   Updated: 2021/10/13 20:54:04 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmd.h"

#define VALID_IDENTIFIER "minishell: unset: `': not a valid identifier\n"

int	my_unset(t_cmd_lst *cmd, t_envlist *envp_lst)
{
	t_cmd_lst	*now;
	t_envlist	*tmp;
	char		*unset_obj;
	char		*env_key;
	int			char_cnt;

	now = cmd->next->next;
	g_status = 0;
	if (now == cmd)
		return (g_status);

	while (now != cmd)
	{
		unset_obj = now->str;
		char_cnt = 0;
		if (unset_obj == NULL || unset_obj[char_cnt] == ' ')
		{
			ft_putstr_fd(VALID_IDENTIFIER, STDERR_FILENO);
			g_status = 1;
			now = now->next;
			continue ;
		}

		while (unset_obj[char_cnt] != '=' && unset_obj[char_cnt])
			char_cnt++;
		env_key = malloc_and_copy(unset_obj, ++char_cnt);
		tmp = envp_lst->next;
		while (tmp != envp_lst && ft_strncmp(tmp->key, env_key, char_cnt))
			tmp = tmp->next;
		if (tmp == envp_lst)
			return (g_status);

		free(tmp->key);
		free(tmp->value);
		ft_envlstdelone(tmp);
		free(env_key);
		now = now->next;
	}
	return (g_status);
}
