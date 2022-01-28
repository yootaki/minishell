/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:41:35 by yootaki           #+#    #+#             */
/*   Updated: 2022/01/29 00:33:26 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmd.h"
#include "expansion.h"

void	expansion_var(t_expanser *expanser, t_envlist *env)
{
	char	*var_name;
	char	*var_value;
	char	*new_str;

	expanser->str[expanser->str_cnt] = '\0';
	var_name = get_var_name(&expanser->str[expanser->str_cnt + 1]);
	var_value = get_var_value(var_name, env);
	if (var_value == NULL)
	{
		new_str = strjoin_minishell(expanser->str, \
		&expanser->str[expanser->str_cnt + ft_strlen(var_name) + 1]);
	}
	else
		new_str = double_strjoin(expanser, var_value, var_name);
	free(var_name);
	free(var_value);
	free(expanser->str);
	if (!ft_strlen(new_str))
		expanser->str = NULL;
	else
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
	while (expanser->str[expanser->str_cnt] != '\0' \
	&& expanser->str[expanser->str_cnt] != '\n')
	{
		quotation_flag_check(expanser);
		if (expanser->str[expanser->str_cnt] == '$' && !expanser->quote_flag \
		&& is_var_name(expanser->str[expanser->str_cnt + 1]))
			expansion_var(expanser, env);
		else
			expanser->str_cnt++;
		if (expanser->str == NULL)
		{
			expanser->str = ft_xstrdup("");
		}
	}
	expanser->str_cnt = 0;
	while (expanser->str[expanser->str_cnt] != '\0' \
	&& expanser->str[expanser->str_cnt] != '\n')
	{
		if (expanser->str[expanser->str_cnt] == '\"')
			delete_quotation_mark(expanser, '\"');
		else if (expanser->str[expanser->str_cnt] == '\'')
			delete_quotation_mark(expanser, '\'');
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
		add_lst_cnt = 0;
		expansionvar_and_deletequote(&expanser, env);
		expanser.str_cnt = 0;
		if (put_separated_expanser_to_now(now, &expanser, &add_lst_cnt))
			return (EXIT_FAILURE);
		if (add_lst_cnt == 0)
		{
			//printf("add_lt_cnt\n");
			now = now->next;
		}
		while (--add_lst_cnt >= 0)
		{
			now->category = categorize(now);
			now = now->next;
		}
		free(expanser.str);
	}
	return (EXIT_SUCCESS);
}

int	expansion(t_nlst *node, t_envlist *envp_lst)
{
	t_nlst	*now;
	t_flag	flag;

	now = node->next;
	while (now != node)
	{
		if (expanser(now->cmd, envp_lst))
			return (EXIT_FAILURE);
		if (change_underbar(now, envp_lst))
			return (EXIT_FAILURE);
		if (heardoc_and_redirect(now->redirect, envp_lst))
			return (EXIT_FAILURE);
		flag = pipe_next_cmd_check(now, envp_lst, node);
		if (flag == FAILURE)
			return (EXIT_FAILURE);
		if (flag == SKIP)
			break ;
		now = now->next;
	}
	return (EXIT_SUCCESS);
}
