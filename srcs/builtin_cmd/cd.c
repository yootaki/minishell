/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:42:16 by yootaki           #+#    #+#             */
/*   Updated: 2021/11/05 13:28:01 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmd.h"
#define CURRENTPATH_SIZE 512

int	change_oldpwd(t_envlist *envp_lst, t_envlist *now_pwd)
{
	t_envlist	*now;

	now = envp_lst->next;
	while (now != envp_lst \
	&& ft_strncmp(now->key, "OLDPWD", ft_strlen("OLDPWD") + 1))
		now = now->next;
	if (now == envp_lst)
		ft_envlstadd_back(envp_lst, ft_envlstnew("OLDPWD", now_pwd->value));
	else
	{
		free(now->value);
		now->value = ft_xstrdup(now_pwd->value);
		if (!now->value)
			exit (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	change_current_path(t_envlist *envp_lst)
{
	t_envlist	*now;
	char		current_path[CURRENTPATH_SIZE];

	ft_memset(current_path, '\0', CURRENTPATH_SIZE);
	if (!getcwd(current_path, CURRENTPATH_SIZE))
		return (EXIT_FAILURE);
	now = envp_lst->next;
	while (now != envp_lst && ft_strncmp(now->key, "PWD", 4))
		now = now->next;
	change_oldpwd(envp_lst, now);
	now->value = ft_xstrdup(current_path);
	if (!now->value)
		exit (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	my_cd(t_cmd_lst *cmd, t_envlist *envp_lst)
{
	t_cmd_lst	*now;
	t_envlist	*tmp;
	char		*dir_path;

	now = cmd->next->next;
	if (now == cmd)
	{
		tmp = envp_lst->next;
		while (ft_strncmp(tmp->key, "HOME", 4) && tmp != envp_lst)
			tmp = tmp->next;
		dir_path = tmp->value;
	}
	else if (now->str == NULL)
		return (0);
	else
		dir_path = now->str;
	if (chdir(dir_path))
	{
		perror(dir_path);
		g_status = 1;
		return (EXIT_FAILURE);
	}
	change_current_path(envp_lst);
	g_status = 0;
	return (EXIT_SUCCESS);
}
