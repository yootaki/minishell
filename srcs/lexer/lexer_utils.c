/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 15:04:40 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/19 15:30:54 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/input.h"

t_token_type	check_type(char *str)
{
	if (*str == CHAR_PIPE)
		return (CHAR_PIPE);
	if (*str == CHAR_QOUTE)
		return (CHAR_QOUTE);
	if (*str == CHAR_DQUOTE)
		return (CHAR_DQUOTE);
	if (ft_strncmp(str, "<<<", 3) == 0)
		return (T_LESSER);
	if (ft_strncmp(str, "<<", 2) == 0)
		return (HEAR_DOC);
	if (*str == CHAR_LESSER)
		return (CHAR_LESSER);
	if (ft_strncmp(str, ">>", 2) == 0)
		return (DGREATER);
	if (*str == CHAR_GREATER)
		return (CHAR_GREATER);
	return (CHAR_GENERAL);
}

void	proceed_command(char **cmd, char *ch, size_t *char_cnt)
{
	while (**cmd != *ch && **cmd != '\0')
	{
		(*cmd)++;
		(*char_cnt)++;
	}
}

bool	check_isdigit(char *str)
{
	size_t	i;
	size_t	j;

	if (str == NULL)
		return (false);
	i = ft_strlen(str);
	j = 0;
	while (j < i && str[j] != '\0')
	{
		if (!ft_isdigit(str[j]))
			return (false);
		j++;
	}
	return (true);
}

void	is_specified_fd(char *cmd, t_tokeniser *data, char *command)
{
	size_t	len;
	char	*str;

	len = data->char_cnt;
	str = ft_substr(command, data->start, data->char_cnt);
	if (check_isdigit(str))
		data->flg = 1;
	free (str);
	return ;
	if (len >= 2)
	{
		if (ft_isdigit(cmd[-1]) && cmd[-2] == CHAR_WHITESPACE)
			data->flg = 1;
	}
	else if (len >= 1)
	{
		if (ft_isdigit(cmd[-1]))
			data->flg = 1;
	}
}

void	is_functions(t_tokeniser **data, char **cmd)
{
	if (ft_isalpha(**cmd) || is_type(**cmd))
		is_alnum(cmd, &(*data)->char_cnt);
	else if (ft_isdigit(**cmd) || is_type(**cmd))
		is_digit(cmd, &(*data)->char_cnt);
	else if (**cmd == CHAR_QOUTE || **cmd == CHAR_DQUOTE)
		is_quort(cmd, &(*data)->char_cnt);
	else
		is_else(cmd, &(*data)->char_cnt);
}
