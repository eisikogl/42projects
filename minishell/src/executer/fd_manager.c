/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 00:44:17 by eisikogl          #+#    #+#             */
/*   Updated: 2024/03/08 16:23:01 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_valid_fd(t_cmd *cmd);

int	define_redirection_fds(void)
{
	t_cmd	*command;
	t_token	*redirections;

	command = g_minishell.command;
	while (command)
	{
		redirections = command->redirections;
		while (redirections)
		{
			if (command->fd_out != -1 || command->fd_in != -1)
			{
				open_redirection_files(redirections->token_type,
					redirections->next->token_value, command);
				redirections = redirections->next;
				redirections = redirections->next;
			}
		}
		if (!is_valid_fd(command))
			return (0);
		command = command->next;
	}
	return (1);
}

void	close_single_fd(t_cmd *command, int fd_type)
{
	if ((fd_type == IN || fd_type == IN_OUT) && command->fd_in > 2)
		close(command->fd_in);
	if ((fd_type == OUT || fd_type == IN_OUT) && command->fd_out > 2)
		close(command->fd_out);
}

void	close_all_fds(void)
{
	t_cmd	*command;

	command = g_minishell.command;
	while (command)
	{
		close_single_fd(command, IN_OUT);
		command = command->next;
	}
}

static int	is_valid_fd(t_cmd *cmd)
{
	if (cmd->fd_in == -3)
	{
		g_minishell.exit_code = 130;
		return (0);
	}
	if (cmd->fd_in == -2)
		cmd->fd_in = STDIN_FILENO;
	if (cmd->fd_out == -2)
		cmd->fd_out = STDOUT_FILENO;
	return (1);
}
