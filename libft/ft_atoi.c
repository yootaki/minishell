/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 09:40:44 by yootaki           #+#    #+#             */
/*   Updated: 2021/05/13 23:07:16 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ovcheck(int sign, long num, long next_num)
{
	long	ov_div;
	long	ov_mod;

	ov_div = LONG_MAX / 10;
	ov_mod = LONG_MAX % 10;
	if (sign == 1 && ((num > ov_div)
			|| (ov_div == num && next_num > ov_mod)))
		return (-1);
	if (sign == -1 && ((num > ov_div)
			|| (ov_div == num && next_num > ov_mod)))
		return (0);
	return (num);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	int			check;
	long		result;

	sign = 1;
	result = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 7 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		check = ft_ovcheck(sign, result, str[i] - '0');
		if (result > 0 && (check == 0 || check == -1))
			return (check);
		result = result * 10 + (str[i++] - '0');
	}
	return ((int)(result * sign));
}
