/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:41:46 by yootaki           #+#    #+#             */
/*   Updated: 2021/09/23 23:18:53y yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmd.h"

#define TOO_MANY_ARGUMENTS "minishell: exit: too many arguments\n"

//数字以外が入っていたら0を返す
static int	is_str_digit(char *str)
{
	if (*str == '-' || *str == '+' || *str == ' ')
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
	{ check = ft_ovcheck(sign, result, str[i] - '0');
		if (result > 0 && (check == 0 || check == -1))
			return (1);
		result = result * 10 + (str[i++] - '0');
	}
	return (0);
}

int	calculate_exit_status(char *str)
{
	long	num;

	num = ft_atoi(str);
	if (num < 0)
	{
		return ((num ^ 0xffffffff) + 1);
	}
	else if (num >= 256)
	{
		return (num % 256);
	}
	return (num);
}

int	my_exit(t_cmd_lst *cmd)
{
	t_cmd_lst	*now;
	char		*args[2];
	int			count;

	count = 0;
	now = cmd->next->next;
	while (now != cmd)
	{
		if (now->str[0] != ' ')
			count++;
		if (count > 2)//引数が3つ以上の場合はexitせずにstatus=1になる
		{
			g_status = 1;
			ft_putstr_fd(TOO_MANY_ARGUMENTS, STDERR_FILENO);
			return (1);
		}
		else if (count > 0)
			args[count - 1] = now->str;
		now = now->next;
	}
	if (count == 1)
	{
		if (args[0][0] == '-' && args[0][1] != '0')
			exit (255);
		// exit (ft_atoi(args[0]));
		exit (calculate_exit_status(args[0]));
	}
	else if (count == 1 && !is_str_digit(args[0]))
		exit (255);
	//引数一つ目が数字で、二つ目が数字じゃないばあ
	if (count == 2 && is_str_digit(args[0]) \
	&& !longlong_over_check(args[0]) && !is_str_digit(args[1]))
		exit (255);
	else if (count == 2 && !is_str_digit(args[0]))
		exit (255);
	else if (count == 2)
	{
		g_status = 1;
		ft_putstr_fd(TOO_MANY_ARGUMENTS, STDERR_FILENO);
		return (1);
	}
	exit (0);
}
