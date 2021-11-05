/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 22:49:41 by hryuuta           #+#    #+#             */
/*   Updated: 2021/04/24 15:08:52 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*cpy_base(char const *s1, char const *s2, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if ((s1 == NULL) && (s2 == NULL))
	{
		str[i] = '\0';
		return (str);
	}
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	st1;
	size_t	st2;
	char	*str;
	char	*st;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	st1 = ft_strlen(s1);
	st2 = ft_strlen(s2);
	str = (char *)malloc(st1 + st2 + 1);
	if (str == NULL)
		return (NULL);
	st = cpy_base(s1, s2, str);
	return (st);
}
