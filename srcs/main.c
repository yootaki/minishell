#include "input.h"
#include "parse.h"
#include "utils.h"
#include "expansion.h"
#include "execution.h"

void	check(t_nlst *nil)
{
	int i = 0;
	t_nlst		*current;
	t_cmd_lst	*c_tmp;
	t_redirect	*r_tmp;

	current = nil->next;
	while (current != nil)
	{
		i = 0;
		c_tmp = current->cmd->next;
		while (c_tmp != current->cmd)
		{
			printf("c_str = %s\n", c_tmp->str);
			printf("c_type = %d\n", c_tmp->c_type);
			c_tmp = c_tmp->next;
			i++;
		}
		i = 0;
		r_tmp = current->redirect->next;
		while (r_tmp != current->redirect)
		{
			printf("r_str = %s\n", r_tmp->str);
			printf("r_type = %d\n", r_tmp->c_type);
			r_tmp = r_tmp->next;
			i++;
		}
		current = current->next;
	}
}

t_nlst	*get_cmdline_from_input_str(char *command, t_envlist *envp_lst)
{
	t_nlst		*node;
	t_tokeniser	data;

	node = init_node();
	if (!node)
		return (NULL);
	lexer(&data, command);
	if (data.token == NULL)
		return (NULL);
	if (parse(node, data.token, envp_lst) == EXIT_FAILURE)
	{
	 	free_node(node);
		return (NULL);
	}
	// check(node);
	return (node);
}

void	loop_shell(char **envp)
{
	t_nlst		*node;
	t_envlist	*envp_lst;
	char		*command;
	int			start;
	size_t		i;

	envp_lst = get_envp(envp);
	read_history(".my_history");
	i = 0;
	start = 0;
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
		expansion(node, envp_lst);
		exection(node);
		signal_ign();
		add_history(command);
		free(command);
		write_history(".my_history");
		//system("leaks minishell");
		i++;
	}
	free_envplist(envp_lst);
}

int main(int argc, char *argv[], char **envp)
{
	argc = 0;
	argv = NULL;
	loop_shell(envp);
	//free(envp);
	//system("leaks minishell");
	return (EXIT_SUCCESS);
}
