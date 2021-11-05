/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_function.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:02:19 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/05 13:46:34 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

bool	is_type(int c)
{
	if (c == '$' || c == '.' || c == '/' || c == '-' || c == '&' \
	|| c == '+' || c == '?' || c == ';' || c == ':' || c == '=' \
	|| c == '_')
		return (true);
	return (false);
}

void	is_alnum(char **cmd, size_t *char_cnt)
{
	while ((ft_isalnum(**cmd) || is_type(**cmd)) && **cmd != '\0')
	{
		(*cmd)++;
		(*char_cnt)++;
	}
}

void	is_digit(char **cmd, size_t *char_cnt)
{
	while ((ft_isdigit(**cmd) || is_type(**cmd)) && **cmd != '\0')
	{
		(*cmd)++;
		(*char_cnt)++;
	}
}

void	is_quort(char **cmd, size_t *char_cnt)
{
	char	ch;

	ch = **cmd;
	(*cmd)++;
	(*char_cnt)++;
	proceed_command(cmd, &ch, char_cnt);
	if (**cmd != '\0')
	{
		(*cmd)++;
		(*char_cnt)++;
		if (**cmd == CHAR_QOUTE || **cmd == CHAR_DQUOTE)
		{
			ch = **cmd;
			(*cmd)++;
			(*char_cnt)++;
			proceed_command(cmd, &ch, char_cnt);
			if (**cmd != '\0')
			{
				(*cmd)++;
				(*char_cnt)++;
			}
		}
	}
}

void	is_else(char **cmd, size_t *char_cnt)
{
	char	ch;
	int		i;

	if (**cmd == CHAR_GREATER || **cmd == CHAR_LESSER)
	{
		ch = **cmd;
		(*cmd)++;
		(*char_cnt)++;
		i = 0;
		while (**cmd != '\0' && **cmd == ch && i < 2)
		{
			if (**cmd == CHAR_GREATER && i == 1)
				break ;
			(*cmd)++;
			(*char_cnt)++;
			i++;
		}
	}
	else
	{
		(*cmd)++;
		(*char_cnt)++;
	}
}
