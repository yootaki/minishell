/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 13:37:28 by yootaki           #+#    #+#             */
/*   Updated: 2021/10/26 20:11:41 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin_cmd/builtin_cmd.h"
#include "../../includes/expansion.h"

void	add_cmd_lst(t_cmd_lst *now)
{
	t_cmd_lst	*newlst;

	newlst = (t_cmd_lst *)xmalloc(sizeof(t_cmd_lst));
	newlst->prev = now;
	newlst->next = now->next;
	now->next->prev = newlst;
	now->next = newlst;
}

int	is_sepalate_char(char c)
{
	if (c == ' ' || c == '\t' || c == '\0')
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}

char	*extract_str(t_expanser *expanser)
{
	int	start;
	int	end;

	start = expanser->str_cnt;
	while (!is_sepalate_char(expanser->str[expanser->str_cnt]))
		expanser->str_cnt++;
	end = expanser->str_cnt;
	if (expanser->str[expanser->str_cnt] == ' ' && start == end)
	{
		while (expanser->str[expanser->str_cnt] == ' ')
			expanser->str_cnt++;
		end = expanser->str_cnt;
	}
	return (ft_xsubstr(expanser->str, start, end - start));
}

void	put_extracted_str_to_now(t_cmd_lst *now, char *extracted_str, int n)
{
	if (n == 0)
	{
		free(now->str);
		now->str = extracted_str;
	}
	else
	{
		add_cmd_lst(now);
		now = now->next;
		now->str = extracted_str;
	}
}

int	put_separated_expanser_to_now(t_cmd_lst *now, t_expanser *expanser, int *n)
{
	char	*extracted_str;

	if (now->prev->str == NULL)
	{
		free(now->str);
		now->str = ft_xstrdup(expanser->str);
		if (!now->str)
			exit (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	else if (expanser->str == NULL || !expanser->str[0])
	{
		free(now->str);
		now->str = NULL;
		return (EXIT_SUCCESS);
	}
	while (expanser->str[expanser->str_cnt] != '\0')
	{
		extracted_str = extract_str(expanser);
		if (!extracted_str)
			exit (EXIT_FAILURE);
		put_extracted_str_to_now(now, extracted_str, *n);
		*n += 1;
	}
	return (EXIT_SUCCESS);
}
