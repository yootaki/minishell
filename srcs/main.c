#include "input.h"
#include "parse.h"
#include "utils.h"
#include "expansion.h"
#include "execution.h"

int	g_status;

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
		//printf("current_p = %p\n", current);
		c_tmp = current->cmd->next;
		//printf("current->cmd = %p\n", current->cmd);
		while (c_tmp != current->cmd)
		{
			//printf("c_str = %s\n", c_tmp->str);
			//printf("c_str_p = %p\n", c_tmp->str);
			//printf("c_type = %d\n", c_tmp->c_type);
			//printf("c_tmp_p = %p\n", c_tmp);
			c_tmp = c_tmp->next;
			i++;
		}
		i = 0;
		r_tmp = current->redirect->next;
		//printf("current->redirect = %p\n", current->redirect);
		while (r_tmp != current->redirect)
		{
			//printf("r_str = %s\n", r_tmp->str);
			//printf("r_str = %p\n", r_tmp->str);
			//printf("r_type = %d\n", r_tmp->c_type);
			//printf("r_tmp_p = %p\n", r_tmp);
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

	//printf("--------get_cmdline_from_input_str_start-----\n");
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
	free_data(&data);
	//free_node(node);
	//printf("--------get_cmdline_from_input_str_end-----\n");
	return (node);
}

void	loop_shell(char **envp)
{
	t_nlst		*node;
	t_envlist	*envp_lst;
	char		*command;

	envp_lst = get_envp(envp);
	read_history(".my_history");
	int i = 0;
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
		if (expansion(node, envp_lst))
			continue ;
		else
		{
			node = get_cmdline_from_input_str(command, envp_lst);
			//free_envplist(envp_lst);
			//printf("------before-----\n");
			//check(node);
			//printf("-----------------\n");
			//expansion(node, envp_lst);
			//printf("------after-----\n");
			//check(node);
			//printf("-----------------\n");
			//free_node(node);
			//free_envplist(envp_lst);
			expansion(node, envp_lst);
			exection(node);
			//free_node(node);
			//free_envplist(envp_lst);
		}
		signal_ign();
		add_history(command);
		//printf("command = %p\n", command);
		free(command);
		write_history(".my_history");
		i++;
	}
	free_envplist(envp_lst);
	//system("leaks minishell");
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	loop_shell(envp);
	//system("leaks minishell");
	return (EXIT_SUCCESS);
}
