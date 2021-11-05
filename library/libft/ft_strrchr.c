/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 03:40:40 by hryuuta           #+#    #+#             */
/*   Updated: 2021/04/26 23:24:31 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char		*p;

	p = s;
	if (c == '\0')
		return ((char *)p + ft_strlen(s));
	p += ft_strlen(s);
	while (*p != c && *p != *s)
		p--;
	if (*p == c)
		return ((char *)p);
	else
		return (NULL);
}
