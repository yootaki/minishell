#include "../builtin_cmd/builtin_cmd.h"
#include "expansion.h"

void	add_cmd_lst(t_cmd_lst *now)
{
	t_cmd_lst	*newlst;

	newlst = (t_cmd_lst *)malloc(sizeof(t_cmd_lst));
	newlst->prev = now;
	newlst->next = now->next;
	now->next->prev = newlst;
	now->next = newlst;
}

int	sep_str(t_cmd_lst *now, t_expanser *expanser)
{
	char	*extract_str;
	int		start;
	int		end;
	int		count;

	count = 0;
	while (1)
	{
		while (expanser->str[expanser->str_cnt] == '$')
			expanser->str_cnt++;
		if (expanser->str[expanser->str_cnt] == '\0')
			return (count);
		start = expanser->str_cnt;
		while (expanser->str[expanser->str_cnt] != '\0' \
		&& expanser->str[expanser->str_cnt] != '$')
			expanser->str_cnt++;
		end = expanser->str_cnt;
		extract_str = ft_substr(expanser->str, start, end - start);
		if (count == 0)
			now->str = extract_str;
		else
		{
			add_cmd_lst(now);
			now = now->next;
			now->str = extract_str;
		}
		count++;
	}
}
