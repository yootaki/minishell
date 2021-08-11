/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 01:01:50 by hryuuta           #+#    #+#             */
/*   Updated: 2021/04/22 16:46:39 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char		*p1;
	const unsigned char	*p2;

	p1 = (unsigned char *)dest;
	p2 = (const unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	while (n > 0)
	{
		*p1 = *p2;
		if (*p1 == (unsigned char )c)
			return ((void *)p1 + 1);
		p1++;
		p2++;
		n--;
	}
	return (NULL);
}
