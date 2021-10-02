/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:41:14 by yootaki           #+#    #+#             */
/*   Updated: 2021/10/01 22:23:21 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin_cmd/builtin_cmd.h"
#include "../../includes/expansion.h"

static char	*join_three_str(char *str_front, char *str_middle, char *str_back)
{
	char	*str_new;
	char	*tmp;

	if (!str_front)
		tmp = ft_strdup(str_middle);
	else if (!str_middle)
		tmp = ft_strdup(str_front);
	else
		tmp = ft_strjoin(str_front, str_middle);
	if (!str_back)
		str_new = tmp;
	else
		str_new = ft_strjoin(tmp, str_back);
	free(tmp);
	return (str_new);
}

char	*create_new_str(t_expanser *expanser, char *str_front, char *str_middle, char *str_back)
{
	if (expanser->str[expanser->str_cnt] == '\0')
		return (ft_strjoin(str_front, str_middle));
	else
	{
		expanser->str[expanser->str_cnt] = '\0';
		if (expanser->str[expanser->str_cnt + 1] != '\0')
			str_back = &expanser->str[expanser->str_cnt + 1];
		else
			str_back = "";
		return (join_three_str(str_front, str_middle, str_back));
	}
}

//dquoteとquoteの処理がほとんど一緒なので後で統合したほうが良さそう
void	delete_dquote(t_expanser *expanser)
{
	char	*str_front;
	char	*str_middle;
	char	*str_back;
	char	*str_new;

	str_front = NULL;
	str_middle = NULL;
	str_back = NULL;
	str_new = NULL;
	expanser->str[expanser->str_cnt] = '\0';
	if (expanser->str_cnt > 0)
		str_front = expanser->str;
	else
		str_front = "";
	expanser->str_cnt++;
	str_middle = &expanser->str[expanser->str_cnt];
	while (expanser->str[expanser->str_cnt] != '\"' && expanser->str[expanser->str_cnt] != '\0')
		expanser->str_cnt++;
	str_new = create_new_str(expanser, str_front, str_middle, str_back);
	if (str_new == NULL)
		exit(EXIT_FAILURE);
	free(expanser->str);
	expanser->str = str_new;
	expanser->str_cnt -= 2;
}

void	delete_quote(t_expanser *expanser)
{
	char	*str_front;
	char	*str_middle;
	char	*str_back;
	char	*str_new;

	str_front = NULL;
	str_middle = NULL;
	str_back = NULL;
	str_new = NULL;
	expanser->str[expanser->str_cnt] = '\0';
	if (expanser->str_cnt > 0)
		str_front = expanser->str;
	else
		str_front = "";
	expanser->str_cnt++;
	str_middle = &expanser->str[expanser->str_cnt];
	while (expanser->str[expanser->str_cnt] != '\'' && expanser->str[expanser->str_cnt] != '\0')
		expanser->str_cnt++;
	str_new = create_new_str(expanser, str_front, str_middle, str_back);
	if (str_new == NULL)
		exit(EXIT_FAILURE);
	free(expanser->str);
	expanser->str = str_new;
	expanser->str_cnt -= 2;
}
