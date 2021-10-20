/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_next_cmd_check_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:04:55 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/19 11:34:46 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expansion.h"

void	xcheck(t_nlst *nil)
{
	t_nlst		*current;
	t_cmd_lst	*c_tmp;
	t_redirect	*r_tmp;

	current = nil->next;
	while (current != nil)
	{
		c_tmp = current->cmd->next;
		while (c_tmp != current->cmd)
		{
			c_tmp = c_tmp->next;
		}
		r_tmp = current->redirect->next;
		while (r_tmp != current->redirect)
		{
			r_tmp = r_tmp->next;
		}
		current = current->next;
	}
}

int	cmd_cmb(char **p_line, char *line)
{
	*p_line = xstrjoin(*p_line, line);
	if (*p_line == NULL)
	{
		free(line);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

char	*xstrjoin(char *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	if (s1 != NULL)
	{
		while (s1[j] != '\0')
			str[i++] = s1[j++];
	}
	j = 0;
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	free((char *)s1);
	return (str);
}

void	nlst_bottom_add(t_nlst *old_node, t_nlst *new_node)
{
	old_node->prev->next = new_node;
	new_node->prev = old_node->prev;
	new_node->next = old_node;
	old_node->prev = new_node;
}

void	delete_node(t_nlst *node, t_nlst *now_node)
{
	if (now_node == node)
		return ;
	now_node->prev->next = now_node->next;
	now_node->next->prev = now_node->prev;
	free(now_node->redirect);
	free(now_node->cmd);
	free(now_node);
}
