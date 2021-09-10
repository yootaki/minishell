#include "../../includes/input.h"
#include "../../includes/parse.h"
#include "../../includes/utils.h"

int	my_echo(t_cmd_lst *cmd, t_redirect *redirect);
int	my_cd(t_cmd_lst *cmd, t_envlist *envp_lst);
int	my_env(t_envlist *envp_lst);
int	my_export(t_cmd_lst *cmd, t_envlist *envp_lst);
int	my_pwd(t_envlist *envp_lst);
int	my_unset(t_cmd_lst *cmd, t_envlist *envp_lst);
int	my_exit(t_cmd_lst *cmd);

int	exec_builtin(t_nlst *node)
{
	char	*cmd;

	cmd = node->next->cmd->next->str;
	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd) + 1))
		my_echo(node->next->cmd, node->next->redirect);
	else if (!ft_strncmp(cmd, "cd", ft_strlen(cmd) + 1))
		my_cd(node->next->cmd, node->next->envp_lst);
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd) + 1))
		my_env(node->next->envp_lst);
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd) + 1))
		my_export(node->next->cmd, node->next->envp_lst);
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		my_pwd(node->next->envp_lst);
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		my_unset(node->next->cmd, node->next->envp_lst);
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		my_exit(node->next->cmd);
	return (EXIT_SUCCESS);
}
