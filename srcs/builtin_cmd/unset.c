/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:43:01 by yootaki           #+#    #+#             */
/*   Updated: 2021/09/27 22:26:45 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmd.h"

#define VALID_IDENTIFIER "minishell: unset: `    TEST': not a valid identifier"

int	my_unset(t_cmd_lst *cmd, t_envlist *envp_lst)
{
	t_envlist	*tmp;
	char		*unset_obj;
	char		*env_key;
	int			char_cnt;

	g_status = 0;
	if (cmd->next->next == cmd)
		return (g_status);
	unset_obj = cmd->next->next->str;
	char_cnt = 0;
	if (unset_obj == NULL || unset_obj[char_cnt] == ' ')
	{
		//エラー処理文の表示仕方考える!!!
		//[unset '   TEST' USER]とかだと、   TESTがエラーを出してg_statusは1。でもUSERはunsetされるみたいな動作をする。
		ft_putstr_fd("minishell: unset: `': not a valid identifier\n", STDERR_FILENO);
		g_status = 1;
		return (g_status);
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
	return (g_status);
}
