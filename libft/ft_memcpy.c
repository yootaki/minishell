/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 19:06:02 by hryuuta           #+#    #+#             */
/*   Updated: 2021/04/22 12:21:56 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	unsigned char		*p1;
	unsigned char		*p2;
	int					i;

	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (!n)
		return (s1);
	i = 0;
	while (n > 0)
	{
		p1[i] = p2[i];
		i++;
		n--;
	}
	return (s1);
}
