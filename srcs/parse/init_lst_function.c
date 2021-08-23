# include "parse.h"

t_cmd_lst	*init_cmd_lst()
{
	t_cmd_lst	*new;

	new = (t_cmd_lst *)malloc(sizeof(t_cmd_lst));
	if (!new)
		return (NULL);
	new->next = new;
	new->prev = new;
	new->c_type = 0;
	new->status = 0;
	new->str = NULL;
	return (new);
}

t_redirect	*init_redirect()
{
	t_redirect	*new;

	new = (t_redirect *)malloc(sizeof(t_redirect));
	if (!new)
		return (NULL);
	new->next = new;
	new->prev = new;
	new->str = NULL;
	new->c_type = 0;
	new->limmiter = NULL;
	new->status = 0;
	return (new);
}

t_nlst	*init_node()
{
	t_nlst	*new;

	new = (t_nlst *)malloc(sizeof(t_nlst));
	if (!new)
		return (NULL);
	new->next = new;
	new->prev = new;
	return (new);
}
