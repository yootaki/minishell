/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:42:40 by yootaki           #+#    #+#             */
/*   Updated: 2021/09/04 11:42:41 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmd.h"

char	*malloc_and_copy(char *str, int size)
{
	char	*new_str;

	new_str = (char *)malloc(sizeof(char) * size);
	if (!new_str)
	{
		perror("malloc");
		return (NULL);
	}
	ft_strlcpy(new_str, str, size);
	return (new_str);
}

int	my_export(t_cmd_lst *cmd, t_envlist *envp_lst)
{
	t_cmd_lst	*now;
	t_envlist	*tmp;
	char		*env_key;
	char		*env_value;
	int			char_cnt;

	now = cmd->next->next;
	char_cnt = 0;
	while (now->str[char_cnt] != '=' && now->str[char_cnt])
		char_cnt++;
	env_key = malloc_and_copy(now->str, char_cnt + 1);
	now->str += char_cnt + 1;
	env_value = malloc_and_copy(now->str, ft_strlen(now->str) + 1);
	tmp = envp_lst->next;
	while (tmp != envp_lst)
	{
		if (!ft_strncmp(tmp->key, env_key, ft_strlen(tmp->key) + 1))
			break ;
		tmp = tmp->next;
	}
	if (tmp != envp_lst)
		tmp->value = now->str;
	else
		ft_envlstadd_back(envp_lst, ft_envlstnew(env_key, env_value));
	return (EXIT_SUCCESS);
}
