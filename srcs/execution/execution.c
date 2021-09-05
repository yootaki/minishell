#include "execution.h"
#include "../builtin_cmd/builtin_cmd.h"

void	init_execution(t_data *data)
{
	data->cmd_array = NULL;
	data->path_list = NULL;
	data->backup_stdout = -1;
}

int	exection(t_nlst *node)
{
	t_data	data;
	char	*cmd;

	cmd = node->next->cmd->next->str;
	//コマンドがビルトインかどうか判定
	init_execution(&data);
	printf("-----------exection_start--------\n");
	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		my_echo(node->next->cmd, node->next->redirect);
	else if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		my_cd(node->next->cmd, node->next->envp_lst);
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		my_env(node->next->envp_lst);
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		my_export(node->next->cmd, node->next->envp_lst);
	else
		execution_process(node, &data);
	printf("-----------exection_end--------\n");
	return (EXIT_SUCCESS);
}
