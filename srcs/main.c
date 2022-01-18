/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:34:02 by yootaki           #+#    #+#             */
/*   Updated: 2022/01/18 11:23:20 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/libft/libft.h"
#include "../includes/input.h"
#include "../includes/parse.h"
#include "../includes/utils.h"
#include "../includes/expansion.h"
#include "../includes/execution.h"

int	g_status;

t_nlst	*get_cmdline_from_input_str(char *command, t_envlist *envp_lst)
{
	t_nlst		*node;
	t_tokeniser	data;

	lexer(&data, command);
	if (data.token == NULL)
		return (NULL);
	node = init_node();
	if (!node)
		return (NULL);
	if (parse(node, data.token, envp_lst) == EXIT_FAILURE)
	{
		free_data(&data);
		free_node(node);
		return (NULL);
	}
	free_data(&data);
	return (node);
}

void	loop_shell(t_envlist *envp_lst)
{
	t_nlst	*node;
	char	*command;

	while (1)
	{
		signal_proc();
		command = readline(MINISHELL);
		if (command == NULL)
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			return ;
		}
		node = get_cmdline_from_input_str(command, envp_lst);
		if (node != NULL)
		{
			if (expansion(node, envp_lst))
			{
				free_node(node);
				continue ;
			}
			exection(node);
		}
		add_history(command);
		free(command);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_envlist	*envp_lst;

	(void)argc;
	(void)argv;
	envp_lst = get_envp(envp);
	ft_putstr_fd("\x1b[36m\
  -----------------------------------------------\n\
                 __      __      __         ____\n\
      ____ ___  /_/___  /_/_____/ /_  ___  / / /\n\
     / __ `__ \\/ / __ \\/ / ____/ __ \\/ _ \\/ / /\n\
    / / / / / / / / / / /___ \\/ / / /  __/ / /\n\
   /_/ /_/ /_/_/_/ /_/_/_____/_/ /_/\\___/_/_/\n\n\
  -----------------------------------------------\n\
            \\\n\
             \\   ^__^\n\
              \\  (oo)\\_______\n\
                 (__)\\       )\\/\\\n\
                     ||----w |\n\
                     ||     ||\n\n\
\x1b[39m", STDERR_FILENO);
	loop_shell(envp_lst);
	free_envplist(envp_lst);
	return (g_status);
}
