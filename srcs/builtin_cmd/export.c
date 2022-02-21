/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:42:40 by yootaki           #+#    #+#             */
/*   Updated: 2021/10/11 21:15:29y yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expansion.h"
#include "builtin_cmd.h"

#define VALID_IDENTIFIER "minishell: export: not valid in this context: \n"

bool	validate_args(char *arg)
{
	if (arg == NULL)
	{
		return (false);
	}
	else if (arg[0] == '=' || arg[0] == ' ' || ft_isdigit(arg[0]))
	{
		return (false);
	}
	else if (!ft_strchr(arg, '='))
	{
		return (false);
	}
	return (true);
}

void	sort_and_print_env(t_envlist *envp_lst)
{
	t_envlist	*new_lst;
	t_envlist	*tmp_new;
	t_envlist	*tmp_src;
	t_envlist	*tmp;
	int			size;

	new_lst = init_envlist();
	tmp_new = new_lst;
	tmp_src = envp_lst->next;
	while (tmp_src != envp_lst)
	{
		ft_envlstadd_back(tmp_new, ft_envlstnew(tmp_src->key, tmp_src->value));
		tmp_src = tmp_src->next;
	}
	size = ft_envlstsize(tmp_new);
	sort_envlst(tmp_new, size);
	tmp = tmp_new->next;
	while (tmp != tmp_new)
	{
		printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

int	insert_key_and_value(t_cmd_lst *now, t_envlist *envp_lst)
{
	t_envlist	*tmp;
	char		*env_key;
	char		*env_value;
	int			char_cnt;

	env_key = NULL;
	env_value = NULL;
	char_cnt = 0;
	while (now->str[char_cnt] != '=' && now->str[char_cnt])
		char_cnt++;
	if (get_key_and_value(now, &env_key, &env_value, char_cnt) == 1)
		return (EXIT_FAILURE);
	tmp = envp_lst->next;
	while (tmp != envp_lst)
	{
		if (!ft_strncmp(tmp->key, env_key, ft_strlen(tmp->key) + 1))
			break ;
		tmp = tmp->next;
	}
	if (tmp != envp_lst)
		set_env_value(tmp, env_key, env_value);
	else
		ft_envlstadd_back(envp_lst, ft_envlstnew(env_key, env_value));
	return (EXIT_SUCCESS);
}

static void	set_insert_key_and_value(t_cmd_lst *now, \
t_cmd_lst *cmd, t_envlist *envp_lst)
{
	while (now != cmd)
	{
		if (!validate_args(now->str))
		{
			ft_putstr_fd(VALID_IDENTIFIER, STDERR_FILENO);
			g_status = 1;
			break ;
		}
		else if (insert_key_and_value(now, envp_lst) == 1)
		{
			g_status = 1;
			break ;
		}
		now = now->next;
	}
}

int	my_export(t_cmd_lst *cmd, t_envlist *envp_lst)
{
	t_cmd_lst	*now;

	now = cmd->next->next;
	if (envp_lst == NULL)
		return (EXIT_SUCCESS);
	g_status = 0;
	if (now == cmd)
	{
		sort_and_print_env(envp_lst);
		return (g_status);
	}
	set_insert_key_and_value(now, cmd, envp_lst);
	return (g_status);
}
