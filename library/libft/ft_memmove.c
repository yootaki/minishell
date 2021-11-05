/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 11:51:31 by hryuuta           #+#    #+#             */
/*   Updated: 2021/04/24 15:20:47 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned char	*cpy_base(unsigned char *s, unsigned char *p, size_t n)
{
	size_t	i;

	i = 0;
	if (s < p)
	{
		i = 0;
		while (i < n)
		{
			s[i] = p[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i > 0)
		{
			s[i - 1] = p[i - 1];
			i--;
		}
	}
	return (s);
}

void	*ft_memmove(void *str1, const void *str2, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned char	*str;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	if (!str1 && !str2)
		return (str1);
	str = cpy_base(s1, s2, n);
	return (str);
}
