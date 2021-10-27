/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:03:32 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/26 19:49:20 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"
#include "../../includes/expansion.h"

char	*ft_xstrjoin(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
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
