/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:34:02 by yootaki           #+#    #+#             */
/*   Updated: 2021/10/20 11:36:21 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	//free_node(node);
	return (node);
}

void	loop_shell(char **envp)
{
	t_nlst		*node;
	t_envlist	*envp_lst;
	char		*command;

	envp_lst = get_envp(envp);
	read_history(".my_history");
	while (1)
	{
		signal_proc();
		command = readline("minishell >> ");
		if (command == NULL)
		{
			free_envplist(envp_lst);
			ft_putstr_fd("\b\b  \b\n", STDERR_FILENO);
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
			else
				exection(node);
		}
		signal_proc();
		add_history(command);
		free(command);
		write_history(".my_history");
	}
	free_envplist(envp_lst);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
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
	loop_shell(envp);
	return (g_status);
}
