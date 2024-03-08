/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 00:43:41 by eisikogl          #+#    #+#             */
/*   Updated: 2024/03/08 16:23:01 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_builtin_command(t_cmd *cmd)
{
	if (!ft_strncmp(cmd->exec[0], "echo\0", 5))
		return (1);
	else if (!ft_strncmp(cmd->exec[0], "pwd\0", 4))
		return (1);
	else if (!ft_strncmp(cmd->exec[0], "cd\0", 3))
		return (1);
	else if (!ft_strncmp(cmd->exec[0], "export\0", 7))
		return (1);
	else if (!ft_strncmp(cmd->exec[0], "unset\0", 6))
		return (1);
	else if (!ft_strncmp(cmd->exec[0], "env\0", 4))
		return (1);
	else if (!ft_strncmp(cmd->exec[0], "exit\0", 5))
		return (1);
	return (0);
}

int	strcmp_eq(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	while (*(s1 + i) || *(s2 + i))
	{
		if (*(s1 + i) != *(s2 + i))
			return (0);
		i++;
	}
	return (1);
}

void	put_msg(char *title, char *msg, int fd)
{
	ft_putstr_fd(title, fd);
	ft_putstr_fd(": ", fd);
	ft_putendl_fd(msg, fd);
	return ;
}

void	send_to_execution_in_parent(t_cmd *command)
{
	if (!ft_strncmp(command->exec_path, "cd\0", 3))
		g_minishell.exit_code = cd_builtin(command);
	else if (!ft_strncmp(command->exec_path, "export\0", 7))
		g_minishell.exit_code = export_builtin(command);
	else if (!ft_strncmp(command->exec_path, "unset\0", 6))
		g_minishell.exit_code = unset_builtin(command);
	else if (!ft_strncmp(command->exec_path, "exit\0", 5))
		g_minishell.exit_code = exit_builtin();
}

void	send_to_execution_in_child(t_cmd *command)
{
	if (!ft_strncmp(command->exec_path, "env\0", 4))
		g_minishell.exit_code = env_builtin(command);
	else if (!ft_strncmp(command->exec_path, "export\0", 7))
		g_minishell.exit_code = export_builtin(command);
	else if (!ft_strncmp(command->exec_path, "echo", 4))
		g_minishell.exit_code = echo_builtin(command->exec);
	else if (!ft_strncmp(command->exec_path, "pwd\0", 4))
		g_minishell.exit_code = pwd_builtin();
}
