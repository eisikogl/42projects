/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 00:44:10 by eisikogl          #+#    #+#             */
/*   Updated: 2024/03/08 16:23:01 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	wait_pids(int pid[1024], int id)
{
	int	max_id;
	int	wstatus;

	if (id == -1)
		return ;
	max_id = id;
	id = -1;
	wstatus = 0;
	while (++id <= max_id)
		waitpid(pid[id], &wstatus, 0);
	if (WIFEXITED(wstatus))
		g_minishell.exit_code = WEXITSTATUS(wstatus);
}

int	is_forked_command(t_cmd *command)
{
	if (!ft_strncmp(command->exec_path, "cd\0", 3)
		|| !ft_strncmp(command->exec_path, "unset\0", 6)
		|| !ft_strncmp(command->exec_path, "exit\0", 5))
	{
		if (!command->is_piped)
			send_to_execution_in_parent(command);
		return (0);
	}
	else if (!ft_strncmp(command->exec_path, "export\0", 7)
		&& command->exec[1] && *command->exec[1])
	{
		if (!command->is_piped)
			send_to_execution_in_parent(command);
		return (0);
	}
	return (1);
}
