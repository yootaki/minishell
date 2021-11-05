/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 22:50:50 by yootaki           #+#    #+#             */
/*   Updated: 2021/11/05 13:28:57 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmd.h"

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

void	ft_sort_envlst(t_envlist *nil, int size)
{
	t_envlist	*min;
	t_envlist	*lst;
	t_envlist	*now;
	int			i;
	int			j;

	i = -1;
	while (++i < size)
	{
		j = i;
		lst = nil->next;
		while (--j >= 0)
			lst = lst->next;
		min = lst;
		now = lst;
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
	ft_sort_envlst(tmp_new, size);
	tmp = tmp_new->next;
	while (tmp != tmp_new)
	{
		printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

int	get_key_and_value(t_cmd_lst *now, char **key, char **val, int cnt)
{
	*key = malloc_and_strlcpy(now->str, cnt + 1);
	if (*key == NULL)
		return (EXIT_FAILURE);
	*val = malloc_and_strlcpy(&now->str[cnt + 1], \
	ft_strlen(&now->str[cnt + 1]) + 1);
	if (*val == NULL)
	{
		free(*key);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
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
	get_key_and_value(now, &env_key, &env_value, char_cnt);
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
