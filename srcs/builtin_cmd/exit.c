/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:41:46 by yootaki           #+#    #+#             */
/*   Updated: 2021/09/27 21:41:49 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmd.h"

#define TOO_MANY_ARGUMENTS "minishell: exit: too many arguments\n"

static int	is_str_digit(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (!*str)
		return (0);
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
			|| (ov_div == num && next_num > ov_mod + 1)))
		return (0);
	return (num);
}

static int	longlong_over_check(const char *str)
{
	int		i;
	int		sign;
	int		check;
	long	result;

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

int	calculate_exit_status(char *str)
{
	long	num;

	if (!is_str_digit(str))
		return (255);
	num = ft_atol(str);
	if (num >= 0 && num <= 255)
		return (num);
	else
		return (num % 256);
}

int	my_exit(t_cmd_lst *cmd)
{
	t_cmd_lst	*now;
	char		*args[2];
	int			count;

	now = cmd->next->next;
	count = 0;
	while (now != cmd)
	{
		if (now->str[0] != ' ')
			count++;
		if (count > 2)
		{
			g_status = 1;
			ft_putstr_fd(TOO_MANY_ARGUMENTS, STDERR_FILENO);
			return (1);
		}
		else if (count > 0)
			args[count - 1] = now->str;
		now = now->next;
	}
	if ((count == 0 && now->next->next->str[0] == ' ') || longlong_over_check(args[0]))
		exit (255);
	if (count == 1)
		exit (calculate_exit_status(args[0]));
	if (count == 2 && is_str_digit(args[0]) \
	&& !longlong_over_check(args[0]) && !is_str_digit(args[1]))
		exit (255);
	else if (count == 2 && !is_str_digit(args[0]))
		exit (255);
	exit (1);
}
