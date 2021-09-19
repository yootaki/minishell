/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sepalate_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 13:37:28 by yootaki           #+#    #+#             */
/*   Updated: 2021/09/19 18:10:51 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin_cmd/builtin_cmd.h"
#include "../../includes/expansion.h"

void	add_cmd_lst(t_cmd_lst *now)
{
	t_cmd_lst	*newlst;

	newlst = (t_cmd_lst *)malloc(sizeof(t_cmd_lst));
	newlst->prev = now;
	newlst->next = now->next;
	now->next->prev = newlst;
	now->next = newlst;
}

/* ここの分割条件は環境変数名と同じ感じにしてもいいかも */
int	is_sepalate_char(char c)
{
	if (c == ' ' || c == '\t' || c == '\0')
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}

int	sep_str(t_cmd_lst *now, t_expanser *expanser)
{
	char	*extract_str;
	int		start;
	int		end;
	int		count;

	count = 0;
	if (now->prev->str == NULL)//t_cmd_lstの先頭はsepせずそのままコマンドとして使うからこの処理
	{
		now->str = ft_strdup(expanser->str);
		return (count);
	}
	while (1)
	{
		if (expanser->str[expanser->str_cnt] == '\0')
			return (count);
		start = expanser->str_cnt;
		while (!is_sepalate_char(expanser->str[expanser->str_cnt]))
			expanser->str_cnt++;
		end = expanser->str_cnt;
		/* ここの条件タブとか入れるか要検討。現在はスペースのみ対応 */
		if (expanser->str[expanser->str_cnt] == ' ' && start == end)
		{
			end = expanser->str_cnt + 1;//ここで最初に代入しておかないとスペースが連続した時に出力が合わない
			while (expanser->str[expanser->str_cnt] == ' ')
				expanser->str_cnt++;
		}
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
