/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:03:32 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/23 19:02:08 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

char	*ft_xstrjoin(char *str1, char *str2)
{
	char	*str;

	str = ft_strjoin(str1, str2);
	if (!str)
	{
		ft_perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (str);
}

char	*ft_xsubstr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	str = ft_substr(s, start, len);
	if (!str)
	{
		ft_perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (str);
}

char	**ft_xsplit(char const *s, char c)
{
	char	**str;

	str = ft_split(s, c);
	if (!str)
	{
		ft_perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (str);
}

char	*ft_xitoa(int n)
{
	char	*str;

	str = ft_itoa(n);
	if (!str)
	{
		ft_perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (str);
}
