/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:43:01 by yootaki           #+#    #+#             */
/*   Updated: 2021/10/14 22:17:23 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmd.h"
#include "../../libft/libft.h"
#include "../../includes/expansion.h"

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
	if (env_key == NULL)
		return (print_error_func("malloc"));//mallocエラーはexitした方がいい？
	tmp = envp_lst->next;
	while (tmp != envp_lst && ft_strncmp(tmp->key, env_key, char_cnt))
		tmp = tmp->next;
	if (tmp == envp_lst)
		return (g_status);
	free(tmp->key);
	free(tmp->value);
	ft_envlstdelone(tmp);
	free(env_key);
	return (g_status);//exitはEXIT_SUCCESSで統一するか、g_statusで統一するか
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
		if (unset_obj == NULL || unset_obj[0] == ' ')
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
