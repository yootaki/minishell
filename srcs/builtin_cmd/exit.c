/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:41:46 by yootaki           #+#    #+#             */
/*   Updated: 2021/09/14 19:53:37 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmd.h"

//数字以外が入っていたら0を返す
static int	is_str_digit(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

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

static int	longlong_over_check(const char *str)
{
	int			i;
	int			sign;
	int			check;
	long		result;

	sign = 1;
	result = 0;
	i = 0;
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
			return (1);
		result = result * 10 + (str[i++] - '0');
	}
	return (0);
}

int	my_exit(t_cmd_lst *cmd)
{
	t_cmd_lst	*now;
	int			count;

	// ft_putstr_fd("exit\n", STDOUT_FILENO);
	now = cmd->next->next;
	count = 0;
	while (now != cmd)
	{
		count++;
		if (count > 2)
			return (255);
		now = now->next;
	}
	now = cmd->next->next;
	if (count == 2 && is_str_digit(now->str) \
	&& !longlong_over_check(now->str) && !is_str_digit(now->next->str))
		return (255);
	return (1);
}
