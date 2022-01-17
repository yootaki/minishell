/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:48:45 by hryuuta           #+#    #+#             */
/*   Updated: 2021/09/15 16:58:17 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;

	ptr = ((unsigned char *)malloc(size * count));
	if (ptr == NULL)
		return (NULL);
	ft_bzero (ptr, size * count);
	return ((void *)ptr);
}
