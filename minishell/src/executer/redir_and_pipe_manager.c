/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_and_pipe_manager.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 00:44:21 by eisikogl          #+#    #+#             */
/*   Updated: 2024/03/08 16:23:01 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	open_redirection_files(int redir_type, char *filename, t_cmd *cmd)
{
	if (redir_type == T_APPEND || redir_type == T_REDIR_OUT)
	{
		if (cmd->fd_out != -2)
			close(cmd->fd_out);
	}
	else if (redir_type == T_HEREDOC || redir_type == T_REDIR_IN)
	{
		if (cmd->fd_in != -2)
			close(cmd->fd_in);
	}
	if (redir_type == T_APPEND)
		cmd->fd_out = open(filename, O_RDWR | O_APPEND | O_CREAT, 0777);
	else if (redir_type == T_REDIR_OUT)
		cmd->fd_out = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0777);
	else if (redir_type == T_HEREDOC)
		cmd->fd_in = heredoc(filename);
	else if (redir_type == T_REDIR_IN)
		cmd->fd_in = open(filename, O_RDONLY);
	cmd->error_number = errno;
	if (errno != 0)
		cmd->filename = filename;
}

void	open_needed_pipes(void)
{
	t_cmd	*command;

	command = g_minishell.command;
	while (command)
	{
		if (command->endpoint == T_PIPE)
		{
			if (pipe(command->fd_pipe) == -1)
			{
				free_minishell();
				exit(1);
			}
			command->fd_out = command->fd_pipe[1];
			command->is_piped = 1;
			command->next->fd_in = command->fd_pipe[0];
			command->next->is_piped = 1;
		}
		command = command->next;
	}
}
