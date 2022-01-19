/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 21:56:39 by yootaki           #+#    #+#             */
/*   Updated: 2022/01/18 13:56:20 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	if (s1 == NULL)
		return (-1);
	if (s2 == NULL)
		return (1);
	while (1)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		if (*s1 == 0)
			return (0);
		s1++;
		s2++;
	}
}
