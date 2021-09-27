/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2021/04/08 09:40:44 by yootaki           #+#    #+#             */
/*   Updated: 2021/09/25 21:41:40 by yootaki          ###   ########.fr       */
=======
/*   Created: 2021/04/12 16:30:56 by hryuuta           #+#    #+#             */
/*   Updated: 2021/09/15 16:58:33 by yootaki          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define LLONG_MAX 9223372036854775807L

static	long	over_num(int sign)
{
	if (sign == 1)
		return (-1);
<<<<<<< HEAD
	if (sign == -1 && ((num > ov_div)
			|| (ov_div == num && next_num > ov_mod + 1)))
=======
	else
>>>>>>> main
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
