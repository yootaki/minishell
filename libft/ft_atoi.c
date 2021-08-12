/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 16:30:56 by hryuuta           #+#    #+#             */
/*   Updated: 2021/04/24 16:19:59 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define	LLONG_MAX 9223372036854775807L

static	long	over_num(int sign)
{
	if (sign == 1)
		return (-1);
	else
		return (0);
}

static	int	is_step(char *str)
{
	int	i;

	i = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n') || \
			(str[i] == '\v') || (str[i] == '\r') || (str[i] == '\f'))
		i++;
	return (i);
}

int	ft_atoi(char *str)
{
	int		sign;
	int		i;
	long	res;
	long	long_div;
	long	long_mod;

	res = 0;
	sign = 1;
	long_div = LLONG_MAX / 10;
	long_mod = LLONG_MAX % 10;
	i = 0;
	i = is_step(str);
	if (str[i] != '\0' && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while ((str[i] != '\0') && (str[i] >= '0') && (str[i] <= '9'))
	{
		if (res > long_div || (res == long_div && str[i] - '0' > long_mod))
			return (over_num(sign));
		res = res * 10 + str[i++] - '0';
	}
	return (res * sign);
}
