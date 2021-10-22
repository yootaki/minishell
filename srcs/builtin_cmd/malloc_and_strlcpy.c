/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_and_strlcpy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 22:20:24 by yootaki           #+#    #+#             */
/*   Updated: 2021/10/22 17:54:51 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expansion.h"

char	*malloc_and_strlcpy(char *str, int size)
{
	char	*new_str;

	new_str = (char *)malloc(sizeof(char) * size);
	if (new_str == NULL)//malloc
		exit (EXIT_FAILURE);
	ft_strlcpy(new_str, str, size);
	return (new_str);
}
