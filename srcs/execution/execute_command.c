/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hryuuta <hryuuta@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:03:53 by hryuuta           #+#    #+#             */
/*   Updated: 2021/10/05 14:03:54 by hryuuta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

char	*tolower_cmd(char *cmd)
{
	int	i;
	int	j;
	char	*str;

	i = ft_strlen(cmd);
	str = (char *)malloc(sizeof(char) * (i +1));
	if (str == NULL)
		return(NULL);
	j = 0;
	while (cmd[j] != '\0')
	{
		str[j] = ft_tolower(cmd[j]);
		j++;
	}
	str[j] = '\0';
	return(str);
}

void	execute_command(t_nlst *node, t_data *data)
{
	char	*cmd;

	cmd = tolower_cmd(node->cmd->next->str);
	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		my_echo(node->cmd, node->redirect);
	else if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		my_cd(node->cmd, node->envp_lst);
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		my_env(node->envp_lst);
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		my_export(node->cmd, node->envp_lst);
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		my_pwd(node->envp_lst);
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		my_unset(node->cmd, node->envp_lst);
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		my_exit(node->cmd);
	else
		no_built_cmd(node, data);
	free(cmd);
}
