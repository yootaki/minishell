#include "input.h"
#include "parse.h"
#include "utils.h"
#include "expansion.h"
#include "execution.h"

/*void	check_env(t_envlist *envp)
{
	int i = 0;
	t_envlist	*e_tmp;
	i = 0;
	e_tmp = envp->next;
	while (e_tmp != envp)
	{
		printf("e_value[%d] = %s\n", i, e_tmp->value);
		printf("e_key[%d] = %s\n", i, e_tmp->key);
		e_tmp = e_tmp->next;
		i++;
	}
}*/

void	check(t_nlst *nil)
{
	int i = 0;
	t_nlst		*current;
	t_cmd_lst	*c_tmp;
	t_redirect	*r_tmp;
	t_envlist	*e_tmp;

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
			//printf("c_type = %d\n", r_tmp->c_type);
			r_tmp = r_tmp->next;
			i++;
		}
		i = 0;
		e_tmp = current->envp_lst->next;
		while (e_tmp != current->envp_lst)
		{
			printf("e_value[%d] = %s\n", i, e_tmp->value);
			//printf("e_key[%d] = %s\n", i, e_tmp->key);
			e_tmp = e_tmp->next;
			i++;
		}
		current = current->next;
	}
}

t_nlst	*get_cmdline_from_input_str(char *command, t_envlist *envp_lst)
{
	t_tokeniser	data;
	t_nlst		*node;

	node = init_node();
	if (!node)
		return (NULL);
	lexer(&data, command);//コマンドライン文字列
	if (data.token == NULL)
		return (NULL);
	if (parse(node, data.token, envp_lst) == EXIT_FAILURE)
	{
		free_data(&data);
	 	free_node(node);
		return (NULL);
	}
	// check(node);
	// free_data(&data);
	// free_node(node);
	return (node);
}

//signal----------------------------------
//ctrl + c
void	sig_int_input()
{
	ft_putstr_fd("\b\b  \b\n", STDERR_FILENO);
	ft_putstr_fd("minishell >> ", STDERR_FILENO);
}
//killコマンド
void	sig_term_input(){}
//ctrl + バックスラッシュ
void	sig_quit_input()
{
	ft_putstr_fd("\b\b  \b\b", STDERR_FILENO);
}

void	signal_proc()
{
	if (signal(SIGINT, sig_int_input) == SIG_ERR)
		perror("signal");
	else if (signal(SIGTERM, sig_term_input) == SIG_ERR)
		perror("signal");
	else if (signal(SIGQUIT, sig_quit_input) == SIG_ERR)
		perror("signal");
}

void	signal_ign()
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		perror("signal");
	else if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("signal");
}
//----------------------------------------

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
	signal_proc();//signal
		command = readline("minishell >> ");
		if (command == NULL)
		{
			free_envplist(envp_lst);
			ft_putstr_fd("\b\b  \b\b", STDERR_FILENO);
			printf("\nSee you again!!!\n");
			return ;
		}
		node = get_cmdline_from_input_str(command, envp_lst);
		/* expansion */
		expansion(node, envp_lst);
		/* Command exection */
		// exec_builtin(node);
		exection(node);
		signal_ign();//signal
		add_history(command);
		free(command);
		write_history(".my_history");
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
