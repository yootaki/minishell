#include "expansion.h"

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
	now_node->prev->next = now_node->next;
	now_node->next->prev = now_node->prev;
	free(now_node->redirect);
	free(now_node->cmd);
	free(now_node);
}