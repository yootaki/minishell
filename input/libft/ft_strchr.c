/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 19:34:25 by hryuuta           #+#    #+#             */
/*   Updated: 2021/04/21 03:52:56 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr (const char *s, int c)
{
	char	*p;
	char	n;

	p = (char *)s;
	n = (char)c;
	if (n == '\0')
		return (p + ft_strlen(s));
	while (*p)
	{
		if (*p == n)
			return (p);
		p++;
	}
	return (NULL);
}
