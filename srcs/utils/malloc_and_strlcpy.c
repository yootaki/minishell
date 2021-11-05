/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_and_strlcpy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 22:20:24 by yootaki           #+#    #+#             */
/*   Updated: 2021/11/05 13:32:03 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*malloc_and_strlcpy(char *str, int size)
{
	char	*new_str;

	new_str = (char *)malloc(sizeof(char) * size);
	if (!new_str)
		exit (print_error_func("malloc"));
	ft_strlcpy(new_str, str, size);
	return (new_str);
}
