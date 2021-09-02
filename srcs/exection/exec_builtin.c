#include "../../includes/input.h"
#include "../../includes/parse.h"
#include "../../includes/utils.h"

int	echo(t_cmd_lst *cmd, t_redirect *redirect);
int	cd(t_cmd_lst *cmd, t_envlist *envp_lst);
int	env(t_envlist *envp_lst);
int	export(t_cmd_lst *cmd, t_envlist *envp_lst);
int	pwd(t_envlist *envp_lst);
int	unset(t_cmd_lst *cmd, t_envlist *envp_lst);

int	exection(t_nlst *node)
{
	char	*cmd;

	cmd = node->next->cmd->next->str;
	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd) + 1))
		echo(node->next->cmd, node->next->redirect);
	else if (!ft_strncmp(cmd, "cd", ft_strlen(cmd) + 1))
		cd(node->next->cmd, node->next->envp_lst);
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd) + 1))
		env(node->next->envp_lst);
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd) + 1))
		export(node->next->cmd, node->next->envp_lst);
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		pwd(node->next->envp_lst);
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		unset(node->next->cmd, node->next->envp_lst);
	return (EXIT_SUCCESS);
}
