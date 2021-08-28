#include "../../includes/input.h"
#include "../../includes/parse.h"
#include "../../includes/utils.h"

int	echo(t_cmd_lst *cmd);
int	cd(t_cmd_lst *cmd, t_envlist *envp_lst);
int	env(t_envlist *envp_lst);
int	export(t_cmd_lst *cmd, t_envlist *envp_lst);

int	exection(t_nlst *node)
{
	char	*cmd;

	cmd = node->next->cmd->next->str;
	//コマンドがビルトインかどうか判定
	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		echo(node->next->cmd);
	else if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		cd(node->next->cmd, node->next->envp_lst);
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		env(node->next->envp_lst);
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		export(node->next->cmd, node->next->envp_lst);
	return (EXIT_SUCCESS);
}
