/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 03:34:25 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/14 03:34:27 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup_gnl(const char *s)
{
	size_t	i;
	size_t	len;
	char	*heap;

	len = ft_strlen_gnl(s);
	heap = (char *)malloc(sizeof(char) * (len + 1));
	if (heap == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		heap[i] = (char)s[i];
		i++;
	}
	heap[i] = '\0';
	return (heap);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	size_t	i;
	size_t	len;

	len = 0;
	while (s[len] != '\n' && s[len] != '\0')
		len++;
	i = 0;
	while (i < (len + 1))
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

void	ft_strcpy_gnl(char *ans, char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1[i] != '\0')
	{
		ans[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\n' && s2[j] != '\0')
		ans[i++] = s2[j++];
	if (s2[j] == '\n')
		ans[i] = '\n';
	else if (s2[j] == '\0')
		ans[i] = '\0';
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	i;
	size_t	size;
	char	*ans;

	size = ft_strlen_gnl(s1);
	i = 0;
	while (s2[i] != '\n' && s2[i] != '\0')
		i++;
	size += i;
	ans = (char *)malloc(sizeof(char) * (size + 1));
	if (ans == NULL)
		return (NULL);
	ft_strcpy_gnl(ans, s1, s2);
	return (ans);
}
