/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:41:14 by yootaki           #+#    #+#             */
/*   Updated: 2021/09/14 15:58:45 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin_cmd/builtin_cmd.h"
#include "../../includes/expansion.h"

static char	*join_three_str(char *str_front, char *str_middle, char *str_back)
{
	char	*new_str;
	char	*tmp;

	if (!str_front)
		tmp = ft_strdup(str_middle);
	else if (!str_middle)
		tmp = ft_strdup(str_front);
	else
		tmp = ft_strjoin(str_front, str_middle);
	if (!str_back)
		new_str = tmp;
	else
		new_str = ft_strjoin(tmp, str_back);
	free(tmp);
	return (new_str);
}

void	delete_dquote(t_expanser *expanser)
{
	char	*str_front;
	char	*str_middle;
	char	*str_back;
	char	*new_str;

	expanser->str[expanser->str_cnt] = '\0';
	if (expanser->str_cnt > 0)
		str_front = expanser->str;
	else
		str_front = "";
	expanser->str_cnt++;
	str_middle = &expanser->str[expanser->str_cnt];
	while (expanser->str[expanser->str_cnt] != '\"')
		expanser->str_cnt++;
	expanser->str[expanser->str_cnt] = '\0';
	if (expanser->str[expanser->str_cnt + 1] != '\0')
		str_back = &expanser->str[expanser->str_cnt + 1];
	else
		str_back = "";
	new_str = join_three_str(str_front, str_middle, str_back);
	free(expanser->str);
	expanser->str = new_str;
	expanser->str_cnt -= 2;
}

void	delete_quote(t_expanser *expanser)
{
	char	*str_front;
	char	*str_middle;
	char	*str_back;
	char	*new_str;

	expanser->str[expanser->str_cnt] = '\0';
	if (expanser->str_cnt > 0)
		str_front = expanser->str;
	else
		str_front = "";
	expanser->str_cnt++;
	str_middle = &expanser->str[expanser->str_cnt];
	while (expanser->str[expanser->str_cnt] != '\'')
		expanser->str_cnt++;
	expanser->str[expanser->str_cnt] = '\0';
	if (expanser->str[expanser->str_cnt + 1] != '\0')
		str_back = &expanser->str[expanser->str_cnt + 1];
	else
		str_back = "";
	new_str = join_three_str(str_front, str_middle, str_back);
	free(expanser->str);
	expanser->str = new_str;
	expanser->str_cnt -= 2;
}
