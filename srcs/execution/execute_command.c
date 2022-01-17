/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yootaki <yootaki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:03:53 by hryuuta           #+#    #+#             */
/*   Updated: 2021/11/05 13:34:48 by yootaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "expansion.h"

char	*tolower_cmd(char *cmd)
{
	int		i;
	int		j;
	char	*str;

	if (cmd == NULL)
		return (NULL);
	i = ft_strlen(cmd);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		exit (print_error_func("malloc"));
	j = 0;
	while (cmd[j] != '\0')
	{
		if (ft_isalpha(cmd[j]))
			str[j] = ft_tolower(cmd[j]);
		else
			str[j] = cmd[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

void	execute_command(t_nlst *node, t_data *data)
{
	char	*cmd;

	if (check_redirect(node, data) == EXIT_FAILURE)
		return ;
	cmd = tolower_cmd(node->cmd->next->str);
	if (cmd == NULL)
		no_built_cmd(node, data);
	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		my_echo(node->cmd);
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
