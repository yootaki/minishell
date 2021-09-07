/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:41:35 by yootaki           #+#    #+#             */
/*   Updated: 2021/09/07 15:59:47 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin_cmd/builtin_cmd.h"
#include "../../includes/expansion.h"

void	init_expanser(t_expanser *expanser, char *str)
{
	expanser->str = str;
	expanser->str_cnt = 0;
	expanser->dquote_flag = 0;
	expanser->quote_flag = 0;
}

void	expansion_var(t_expanser *expanser, t_envlist *env)
{
	char	*var_name;
	char	*var_value;
	char	*new_str;
	char	*tmp;

	expanser->str[expanser->str_cnt] = '\0';
	var_name = get_var_name(&expanser->str[expanser->str_cnt + 1]);
	var_value = ft_strdup(get_var_value(var_name, env));
	tmp = ft_strjoin(expanser->str, var_value);
	new_str = ft_strjoin(tmp, \
	&expanser->str[expanser->str_cnt + ft_strlen(var_name) + 1]);
	expanser->str_cnt += ft_strlen(var_value);
	free(var_name);
	free(var_value);
	free(tmp);
	free(expanser->str);
	expanser->str = new_str;
}

void	quotation_flag_check(t_expanser *expanser)
{
	if (expanser->str[expanser->str_cnt] == '\"' \
	&& !expanser->dquote_flag && !expanser->quote_flag)
		expanser->dquote_flag = 1;
	else if (expanser->str[expanser->str_cnt] == '\"' \
	&& expanser->dquote_flag)
		expanser->dquote_flag = 0;
	else if (expanser->str[expanser->str_cnt] == '\'' \
	&& !expanser->quote_flag && !expanser->dquote_flag)
		expanser->quote_flag = 1;
	else if (expanser->str[expanser->str_cnt] == '\'' \
	&& expanser->quote_flag)
		expanser->quote_flag = 0;
}

int	expansionvar_and_deletequote(t_expanser *expanser, t_envlist *env)
{
	while (expanser->str[expanser->str_cnt] != '\0')
	{
		quotation_flag_check(expanser);
		if (expanser->str[expanser->str_cnt] == '$' && !expanser->quote_flag)
			expansion_var(expanser, env);
		else
			expanser->str_cnt++;
	}
	expanser->str_cnt = 0;
	while (expanser->str[expanser->str_cnt] != '\0')
	{
		if (expanser->str[expanser->str_cnt] == '\"')
			delete_dquote(expanser);
		else if (expanser->str[expanser->str_cnt] == '\'')
			delete_quote(expanser);
		expanser->str_cnt++;
	}
	return (EXIT_SUCCESS);
}

int	expanser(t_cmd_lst *cmd, t_envlist *env)
{
	t_expanser	expanser;
	t_cmd_lst	*now;
	int			add_lst_cnt;

	now = cmd->next;
	while (now != cmd)
	{
		init_expanser(&expanser, now->str);
		add_lst_cnt = 1;
		expansionvar_and_deletequote(&expanser, env);
		expanser.str_cnt = 0;
		add_lst_cnt = sep_str(now, &expanser);
		while (--add_lst_cnt >= 0)
		{
			now->category = categorize(now);
			now = now->next;
		}
	}
	return (EXIT_SUCCESS);
}
