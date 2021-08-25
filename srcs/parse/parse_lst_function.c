#include "parse.h"

int	cmd_lst_add(t_cmd_lst *nil, t_token *token)
{
	t_cmd_lst	*new;

	new = (t_cmd_lst *)malloc(sizeof(t_cmd_lst));
	if (!new)
		return (EXIT_FAILURE);
	new->status = 0;
	new->c_type = token->type;
	new->str = token->str;
	nil->prev->next = new;
	new->prev = nil->prev;
	new->next = nil;
	nil->prev = new;
	return (EXIT_SUCCESS);
}

int	redirect_lst_add(t_redirect *nil, t_token *tokens)
{
	t_redirect	*new;

	new = (t_redirect *)malloc(sizeof(t_redirect));
	if (!new)
		return (EXIT_FAILURE);
	new->status = 0;
	new->c_type = tokens->type;
	new->str = tokens->str;
	if (new->c_type == HEAR_DOC)
		new->limmiter = tokens->next->str;
	else
		new->limmiter = NULL;
	nil->prev->next = new;
	new->prev = nil->prev;
	new->next = nil;
	nil->prev = new;
	return (EXIT_SUCCESS);
}

int	nlst_add(t_nlst *nil, t_envlist *env_lst)
{
	t_nlst	*new;

	new = (t_nlst *)malloc(sizeof(t_nlst));
	if (!new)
		return (EXIT_FAILURE);
	new->cmd = init_cmd_lst();
	new->redirect = init_redirect();
	new->envp_lst = env_lst;
	if (!new->cmd || !new->redirect)
		return (EXIT_FAILURE);
	nil->prev->next = new;
	new->prev = nil->prev;
	new->next = nil;
	nil->prev = new;
	return (EXIT_SUCCESS);
}