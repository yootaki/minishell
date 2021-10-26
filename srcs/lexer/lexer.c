/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:02:25 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/26 16:29:21 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/input.h"
#include "../../includes/expansion.h"

int	put_in_list(t_tokeniser *data, char **command, char **cmd)
{
	char	*str;
	t_token	*new_list;

	str = ft_xsubstr(*command, data->start, data->char_cnt);
	new_list = lst_new(str, data->flg);
	lstadd_back(&data->token, new_list);
	data->start = 0;
	data->char_cnt = 0;
	*command = *cmd;
	return (EXIT_SUCCESS);
}

bool	is_delimiter(char *cmd)
{
	if (*cmd == CHAR_WHITESPACE || *cmd == '\0' || *cmd == CHAR_PIPE \
	|| *cmd == CHAR_LESSER || *cmd == CHAR_GREATER || ((cmd[-1] == CHAR_PIPE \
	|| cmd[-1] == CHAR_LESSER || cmd[-1] == CHAR_GREATER) && (ft_isalnum(*cmd) \
	|| is_type(*cmd))))
		return (true);
	return (false);
}

int	sep_command_line(char *command, char *cmd, t_tokeniser *data)
{
	advance_space(&data, &cmd);
	if (*cmd == '\0')
		return (EXIT_SUCCESS);
	is_functions(&data, &cmd);
	if (is_delimiter(cmd))
	{
		if (cmd[0] == CHAR_GREATER || cmd[0] == CHAR_LESSER)
			is_specified_fd(data, command);
		if (put_in_list(data, &command, &cmd) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		data->flg = 0;
	}
	if (*cmd != '\0')
		sep_command_line(command, cmd, data);
	return (EXIT_SUCCESS);
}

int	character_separator(char *command, t_tokeniser *data)
{
	char	*cmd;

	cmd = command;
	if (sep_command_line(command, cmd, data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	lexer(t_tokeniser *data, char *command)
{
	init_data(data, command);
	if (character_separator(command, data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
