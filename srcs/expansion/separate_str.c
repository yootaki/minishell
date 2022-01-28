/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 13:37:28 by yootaki           #+#    #+#             */
/*   Updated: 2022/01/29 00:56:08 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmd.h"
#include "expansion.h"

void	add_cmd_lst(t_cmd_lst *now)
{
	t_cmd_lst	*newlst;

	newlst = (t_cmd_lst *)xmalloc(sizeof(t_cmd_lst));
	newlst->prev = now;
	newlst->next = now->next;
	now->next->prev = newlst;
	now->next = newlst;
	//printf("now->str = %s$\n",now->str);
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
	//printf("start = %d\n", start);
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

void print_check(t_cmd_lst *now)
{
	t_cmd_lst *current;

	current = now->next;
	while (now->str != NULL)
	{
		now = now->next;
	}
		//now = now->next;
	current = now->next;
	while (current != now)
	{
		//printf("current->str = %s$\n", current->str);
		current = current->next;
	}
}

void	put_extracted_str_to_now(t_cmd_lst **now, char *extracted_str, int n)
{
	//printf("put_extracted_str_to_now\n");
	//printf("n = %d\n", n);
	//size_t	size;

	//size = 1;
	if (n == 0)
	{
		free((*now)->str);
		//printf("extracted_str = %s\n", extracted_str);
		//printf("n_extracted_str\n");
		//printf("n_extracted_str = %s:\n", extracted_str);
		(*now)->str = extracted_str;
		//printf("--------if-------\n");
		//print_check(now->prev);
	}
	else
	{
		/* add_cmd_lst(now);
		now = now->next; */
		//printf("extracted_str = %s\n", extracted_str);
		//now->str = extracted_str;
		//printf("extracted_str = %s:\n", extracted_str);
		//printf("extracted_str = %s:\n", extracted_str);
		if (extracted_str[0] != ' ')
		{
			printf("aaaaaa\n");
			printf("--------1-------\n");
			print_check(*now);
			printf("--------2-------\n");
			add_cmd_lst(*now);
			*now = (*now)->next;
			(*now)->str = extracted_str;
			print_check(*now);
			printf("--------3-------\n");
		}
		/* else
		{
			printf("bbbb\n");
			printf("--------1-------\n");
			print_check(*now);
			printf("--------2-------\n");
			add_cmd_lst(*now);
			*now = (*now)->next;
			(*now)->str = extracted_str;
			print_check(*now);
			printf("--------3-------\n");
		} */
		//printf("--------else-------\n");
		//print_check(now->prev);
	}
}



int	put_separated_expanser_to_now(t_cmd_lst *now, t_expanser *expanser, int *n)
{
	//char	*extracted_str;

	/* printf("now->str = %s\n", now->str);
	print_check(now); */
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
	free(now->str);
	now->str = ft_xstrdup(expanser->str);
	/* printf("-------------miduam----------\n");
	print_check(now->prev); */
	/* printf("expanser->str = %s\n", expanser->str);
	print_check(now); */
	//printf("-------------start------------------\n");
	/* while (expanser->str[expanser->str_cnt] != '\0')
	{
		printf("----------------while_strat--------------\n");
		//print_check(now);
		printf("expanser->str_cnt = %d\n", expanser->str_cnt);
		printf("expanser->str = %s\n", expanser->str);
		printf("len = %zu\n", ft_strlen(expanser->str));
		printf("char = $%c$\n", expanser->str[ft_strlen(expanser->str)]);
		extracted_str = extract_str(expanser);
		printf("extracted_str = $%s$\n", extracted_str);
		printf("expanser->str_cnt = %d\n", expanser->str_cnt);
		printf("-------------1---------\n");
		print_check(now->prev);
		if (!extracted_str)
			exit (EXIT_FAILURE);
		put_extracted_str_to_now(&now, extracted_str, *n);
		printf("-------------2----------\n");
		print_check(now->prev);
		*n += 1;
		//print_check(now);
		printf("----------------while_end--------------\n");
	} */
	*n =0;
	//printf("-------------end------------------\n");
	//printf("----------put_separated_expanser_to_now_LAST----------\n");
	//print_check(now);
	return (EXIT_SUCCESS);
}
