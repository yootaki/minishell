/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:43:01 by yootaki           #+#    #+#             */
/*   Updated: 2021/09/04 11:43:02 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmd.h"

int	my_unset(t_cmd_lst *cmd, t_envlist *envp_lst)
{
	t_envlist	*tmp;
	char		*unset_obj;
	char		*env_key;
	int			char_cnt;

	unset_obj = cmd->next->next->str;
	char_cnt = 0;
	while (unset_obj[char_cnt] != '=' && unset_obj[char_cnt])
		char_cnt++;
	env_key = malloc_and_copy(unset_obj, ++char_cnt);
	tmp = envp_lst->next;
	while (tmp != envp_lst && ft_strncmp(tmp->key, env_key, char_cnt))
		tmp = tmp->next;
	if (tmp == envp_lst)
		return (EXIT_SUCCESS);
	free(tmp->key);
	free(tmp->value);
	ft_envlstdelone(tmp);
	free(env_key);
	return (EXIT_SUCCESS);
}
