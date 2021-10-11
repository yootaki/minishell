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

#include "builtin_cmd.h"
#include "../../includes/utils.h"

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

int	ft_strcmp(const char *str1, const char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1 += 1;
		str2 += 1;
	}
	return (0);
}

void	swap_envlst(t_envlist *now, t_envlist *min)
{
	char	*now_key;
	char	*now_value;
	char	*min_key;
	char	*min_value;

	now_key = now->key;
	now_value = now->value;
	min_key = min->key;
	min_value = min->value;
	now->key = min_key;
	now->value = min_value;
	min->key = now_key;
	min->value = now_value;
}

void	ft_sort_envlst(t_envlist *nil)
{
	t_envlist	*min;
	t_envlist	*lst;
	t_envlist	*now;
	int			size;
	int			i;
	int			j;

	size = ft_envlstsize(nil);
	i = -1;
	while (++i < size)
	{
		j = i;
		lst = nil->next;
		min = nil->next;
		now = nil->next;
		while (--j >= 0)
		{
			lst = lst->next;
			min = min->next;
			now = now->next;
		}
		lst = lst->next;
		while (lst != nil)
		{
			if (strcmp(min->key, lst->key) > 0)
				min = lst;
			lst = lst->next;
		}
		swap_envlst(now, min);
	}
}

void	sort_and_print_env(t_envlist *envp_lst)
{
	t_envlist	*new_lst;
	t_envlist	*tmp_new;
	t_envlist	*tmp_src;
	t_envlist	*tmp;

	//create new envlst
	new_lst = init_envlist();
	tmp_new = new_lst;
	tmp_src = envp_lst->next;
	while (tmp_src != envp_lst)
	{
		ft_envlstadd_back(tmp_new, ft_envlstnew(tmp_src->key, tmp_src->value));
		tmp_src = tmp_src->next;
	}

	//sort env
	ft_sort_envlst(tmp_new);

	//print env
	tmp = tmp_new->next;
	while (tmp != tmp_new)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(tmp->key, STDERR_FILENO);
		ft_putstr_fd("=", STDERR_FILENO);
		ft_putstr_fd(tmp->value, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		tmp = tmp->next;
	}
}

int	my_export(t_cmd_lst *cmd, t_envlist *envp_lst)
{
	t_cmd_lst	*now;
	t_envlist	*tmp;
	char		*env_key;
	char		*env_value;
	int			char_cnt;

	now = cmd->next->next;
	if (now == cmd)
	{
		sort_and_print_env(envp_lst);
		return (EXIT_SUCCESS);
	}
	char_cnt = 0;
	while (now->str[char_cnt] != '=' && now->str[char_cnt])
		char_cnt++;
	env_key = malloc_and_copy(now->str, char_cnt + 1);
	env_value = malloc_and_copy(&now->str[char_cnt + 1], ft_strlen(&now->str[char_cnt + 1]) + 1);
	tmp = envp_lst->next;
	while (tmp != envp_lst)
	{
		if (!ft_strncmp(tmp->key, env_key, ft_strlen(tmp->key) + 1))
			break ;
		tmp = tmp->next;
	}
	if (tmp != envp_lst)
		tmp->value = &now->str[char_cnt + 1];
	else
		ft_envlstadd_back(envp_lst, ft_envlstnew(env_key, env_value));
	return (EXIT_SUCCESS);
}
