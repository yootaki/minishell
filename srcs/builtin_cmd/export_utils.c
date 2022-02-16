/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 22:50:50 by yootaki           #+#    #+#             */
/*   Updated: 2022/02/16 09:49:17 by yootaki          ###   ########.fr       */
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

void	sort_envlst(t_envlist *nil, int size)
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

void	set_env_value(t_envlist *current, char *key, char *value)
{
	free(key);
	free(current->value);
	current->value = value;
}
