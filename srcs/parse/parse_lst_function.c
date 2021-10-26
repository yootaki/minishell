/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lst_function.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:02:56 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/26 12:59:37 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

void	cmd_lst_add(t_cmd_lst *nil, t_token *token)
{
	t_cmd_lst	*new;

	new = (t_cmd_lst *)xmalloc(sizeof(t_cmd_lst));
	new->status = 0;
	new->c_type = token->type;
	new->str = token->str;
	nil->prev->next = new;
	new->prev = nil->prev;
	new->next = nil;
	nil->prev = new;
}

void	redirect_lst_add(t_redirect *nil, t_token *tokens)
{
	t_redirect	*new;

	new = (t_redirect *)xmalloc(sizeof(t_redirect));
	new->status = 0;
	new->c_type = tokens->type;
	new->str = tokens->str;
	if (new->c_type == HEAR_DOC)
	{
		if (tokens->next == NULL)
			new->limmiter = NULL;
		else
			new->limmiter = tokens->next->str;
	}
	else
		new->limmiter = NULL;
	nil->prev->next = new;
	new->prev = nil->prev;
	new->next = nil;
	nil->prev = new;
}

void	nlst_add(t_nlst *nil, t_envlist *env_lst)
{
	t_nlst	*new;

	new = (t_nlst *)xmalloc(sizeof(t_nlst));
	new->cmd = init_cmd_lst();
	new->redirect = init_redirect();
	new->envp_lst = env_lst;
	nil->prev->next = new;
	new->prev = nil->prev;
	new->next = nil;
	nil->prev = new;
}
