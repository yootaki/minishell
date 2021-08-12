/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 23:59:06 by hryuuta           #+#    #+#             */
/*   Updated: 2021/04/24 15:24:49 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	is_separater(char s, char c)
{
	if (s == c || s == '\0')
		return (1);
	else
		return (0);
}

static	char	*ft_strncpy2(char **ptr, char const *src, unsigned int n, int k)
{
	unsigned int	i;

	ptr[k] = (char *)malloc(sizeof(char) * (n + 1));
	if (ptr[k] == NULL)
	{
		while (k <= 0)
		{
			free(ptr[k]);
			ptr[k] = NULL;
			k--;
		}
		return (NULL);
	}
	i = 0;
	while ((i < n) && (src[i] != '\0'))
	{
		ptr[k][i] = src[i];
		i++;
	}
	ptr[k][i] = '\0';
	return (ptr[k]);
}

static	char	**make_array(char const *s, char c, char **ptr)
{
	size_t	j;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (s[i] != '\0')
	{
		j = 0;
		if (is_separater(s[i], c) == 1)
			i++;
		else
		{
			while (is_separater(s[i + j], c) == 0)
				j++;
			ft_strncpy2(ptr, &s[i], j, k);
			i += j;
			k++;
		}
	}
	return (ptr);
}

static	size_t	count_array(char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (is_separater(s[i], c) == 0)
		{
			if (is_separater(s[i + 1], c) == 1 || s[i + 1] == '\0')
				j++;
		}
		i++;
	}
	return (j);
}

char 	**ft_split(char const *s, char c)
{
	size_t		array_size;
	char		**ptr;
	char		**result;

	if (s == NULL)
		return (NULL);
	array_size = count_array(s, c);
	ptr = (char **)malloc(sizeof(char *) * (array_size + 1));
	if (ptr == NULL)
		return (NULL);
	result = make_array(s, c, ptr);
	if (result == NULL)
	{
		free(ptr);
		ptr = NULL;
		return (NULL);
	}
	result[array_size] = NULL;
	return (result);
}
