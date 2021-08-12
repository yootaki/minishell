/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 17:18:36 by hryuuta           #+#    #+#             */
/*   Updated: 2021/04/22 12:06:41 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr (const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[i] != '\0' && i < len)
	{
		j = 0;
		if (to_find[j++] == str[i])
		{
			while (to_find[j] && str[i + j] && to_find[j] == str[i + j])
				j++;
			if (!(to_find[j]) && (i + j) <= len)
				return ((char *)&str[i]);
		}
		i++;
	}
	return (NULL);
}
