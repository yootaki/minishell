/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heardoc_and_redirect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 11:41:50 by yootaki           #+#    #+#             */
/*   Updated: 2021/09/20 16:52:07 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin_cmd/builtin_cmd.h"
#include "../../includes/expansion.h"

#define ERR_SYNTAX_NULL "minishell: syntax error near unexpected token `newline'\n"
#define ERR_SYNTAX_FILEIN "minishell: syntax error near unexpected token `<'\n"
#define ERR_SYNTAX_FILEOUT "minishell: syntax error near unexpected token `>'\n"
#define ERR_SYNTAX_FILEAPPEND "minishell: syntax error near unexpected token `>>'\n"
#define ERR_SYNTAX_PIPE "minishell: syntax error near unexpected token `|'\n"

int	print_error_func(char *err_func)
{
	perror(err_func);
	return (EXIT_FAILURE);
}

void	print_syntax_error(char *str, int status)
{
	ft_putstr_fd(str, STDERR_FILENO);
	g_status = status;
}

//<<<の対応、<<<と>><の違いを対応
//コメントアウト部分を外すとなぜかテストの時だけ無限ループ。手打ちだとならない？
int	check_redirect_syntax(t_redirect *now)
{
	if (now->str == NULL)
		print_syntax_error(ERR_SYNTAX_NULL, 2);
	else if (*(now->str) == '<' && *(now->str + 1) == '<')
		print_syntax_error(ERR_SYNTAX_FILEIN, 2);
	// else if (*(now->str) == '<' \
	// && !ft_strncmp(now->prev->str, "<<", ft_strlen("<<") + 1))
	// 	return (EXIT_SUCCESS);
	else if (*(now->str) == '<')
		print_syntax_error(ERR_SYNTAX_FILEIN, 2);
	else if (*(now->str) == '>' && *(now->str + 1) == '>')
		print_syntax_error(ERR_SYNTAX_FILEAPPEND, 2);
	else if (*(now->str) == '>')
		print_syntax_error(ERR_SYNTAX_FILEOUT, 2);
	else if (*(now->str) == '|')
		print_syntax_error(ERR_SYNTAX_PIPE, 2);
	else
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

//expanded_lineがmallocしてる
int	heardoc_and_redirect(t_redirect *redirect, t_envlist *env)
{
	t_redirect	*now;

	now = redirect->next;
	if (now->str == NULL)
		return (EXIT_SUCCESS);
	while (now != redirect)
	{
		if (!ft_strncmp(now->str, "<<", ft_strlen("<<") + 1))
		{
			now = now->next;
			if (check_redirect_syntax(now))
				exit(g_status);//ここはexitするのが正解？returnが正解？
				//cat <<< end がきた場合に、now->next->strを標準出力に入れてあげて終了。heardocはしない。を対応すること。
			hear_doc(now, env, now->str);
		}
		if (!ft_strncmp(now->str, "<", ft_strlen("<") + 1) \
		|| !ft_strncmp(now->str, ">", ft_strlen(">") + 1) \
		|| !ft_strncmp(now->str, ">>", ft_strlen(">>") + 1))
		{
			now = now->next;
			if (check_redirect_syntax(now))
				exit(g_status);//ここはexitするのが正解？returnが正解？
			redirect_file_open(now, env);
		}
		now = now->next;
	}
	return (EXIT_SUCCESS);
}
