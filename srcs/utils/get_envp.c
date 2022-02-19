/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:03:11 by hryuuta           #+#    #+#             */
/*   Updated: 2022/02/19 16:13:34 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	envp_lstmap(t_envlist *envp, char *key, char *value)
{
	t_envlist	*new_lst;

	new_lst = ft_envlstnew(key, value);
	envp->prev->next = new_lst;
	new_lst->prev = envp->prev;
	new_lst->next = envp;
	envp->prev = new_lst;
	return (EXIT_SUCCESS);
}

/*
* 環境変数を一行ずつ読み取り、keyとvalueに分割してenv_lstに追加
*/

int	create_envlst(t_envlist *lst, char **envp)
{
	t_envlist	*current;
	char		*str;
	char		*key;
	char		*value;

	current = lst;
	while (*envp != NULL)
	{
		str = *envp;
		while (*str != '=')
			str++;
		*str = '\0';
		key = ft_xstrdup(*envp);
		str++;
		if (!ft_strncmp(key, "SHLVL", 6))
		{
			value = ft_xitoa(ft_atoi(str) + 1);
			if (ft_atoi(value) > 999)
				value = ft_xitoa((int)1);
		}
		else
			value = ft_xstrdup(str);
		envp_lstmap(current, key, value);
		(envp)++;
	}
	return (EXIT_SUCCESS);
}

t_envlist	*get_envp(char **envp)
{
	t_envlist	*env_lst;
	
	if (envp[0] == NULL)
		return (NULL);
	env_lst = init_envlist();
	create_envlst(env_lst, envp);
	return (env_lst);
}
