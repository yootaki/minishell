/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:41:46 by yootaki           #+#    #+#             */
/*   Updated: 2022/02/19 15:16:45 yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmd.h"

#define TOO_MANY_ARGUMENTS "minishell: exit: too many arguments\n"
#define NUMERIC_ARGUMENT_REQUIRED "minishell: exit: numeric argument required\n"

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

void	determine_status_code_and_exit(t_cmd_lst *now, int count, char **args)
{
	if ((count == 0 && now->next->next->str[0] == ' ') \
	|| longlong_over_check(args[0]))
	{
		g_status = 255;
	}
	else if (count == 1)
	{
		g_status = calculate_exit_status(args[0]);
	}
	else if (count == 2 && is_str_digit(args[0]))
	{
		g_status = 1;
		ft_putstr_fd(TOO_MANY_ARGUMENTS, STDERR_FILENO);
		return ;
	}
	else if (count == 2 && !is_str_digit(args[0]))
	{
		g_status = 255;
		ft_putstr_fd(NUMERIC_ARGUMENT_REQUIRED, STDERR_FILENO);
	}
	exit(g_status);
}

int	my_exit(t_cmd_lst *cmd)
{
	t_cmd_lst	*now;
	char		*args[2];
	int			count;

	g_status = 0;
	now = cmd->next->next;
	if (now == cmd)
		exit(g_status);
	count = 0;
	while (now != cmd)
	{
		if (now->str[0] != ' ')
			count++;
		if (count > 2)
		{
			g_status = 1;
			ft_putstr_fd(TOO_MANY_ARGUMENTS, STDERR_FILENO);
			return (g_status);
		}
		else if (count > 0)
			args[count - 1] = now->str;
		now = now->next;
	}
	determine_status_code_and_exit(now, count, args);
	return (g_status);
}
