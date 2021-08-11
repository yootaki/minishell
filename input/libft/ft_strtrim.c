/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 11:25:19 by hryuuta           #+#    #+#             */
/*   Updated: 2021/04/22 12:51:27 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	trim_c_check(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static	size_t	trim_len_check(char const *s1, char const *set)
{
	size_t	len;
	int		j;

	len = ft_strlen(s1);
	j = 0;
	while (s1[j] != '\0')
	{
		if (trim_c_check(set, s1[j]) == 1)
			len--;
		else
			break ;
		j++;
	}
	if (s1[j] == '\0')
		return (len);
	j = 0;
	while ((ft_strlen(s1) - (j + 1)) >= 0)
	{
		if (trim_c_check(set, s1[ft_strlen(s1) - (j + 1)]) == 1)
			len-- ;
		else
			break ;
		j++;
	}
	return (len);
}

static	int	trim_c_count(char const *s1, char const *set)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (s1[k] != '\0')
	{
		if (trim_c_check(set, s1[k]) == 1)
			i++;
		else
			break ;
		k++;
	}
	if (s1[k] == '\0')
		return (0);
	else
		return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	int		sum;
	int		i;
	int		k;
	char	*str;

	i = 0;
	k = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	len = trim_len_check(s1, set);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	i = trim_c_count(s1, set);
	sum = len + i;
	k = 0;
	while (i < sum)
	{
		str[k++] = s1[i++];
	}
	str[k] = '\0';
	return (str);
}
