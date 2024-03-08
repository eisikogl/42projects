/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_producer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 00:44:08 by eisikogl          #+#    #+#             */
/*   Updated: 2024/03/08 16:23:01 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	execution_error(char *filename, int error_number);
static void	check_pid(t_cmd **command, pid_t pid[1024], int id);
static void	child_execution(t_cmd *command);
static void	command_execution(t_cmd **command);

void	execution_phase(void)
{
	t_cmd	*command;

	command = g_minishell.command;
	open_needed_pipes();
	if (!define_redirection_fds())
		return ;
	while (command)
	{
		command_execution(&command);
		if (command)
			command = command->next;
	}
}

static void	execution_error(char *filename, int error_number)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(filename, 2);
	if (error_number == EACCES)
	{
		ft_putstr_fd(": Permission denied\n", 2);
		g_minishell.exit_code = EXIT_FAILURE;
	}
	else if (error_number == ENOENT)
	{
		ft_putstr_fd(": No such file or directory\n", 2);
		g_minishell.exit_code = EXIT_FAILURE;
	}
	else
	{
		ft_putstr_fd(": Command not found\n", 2);
		g_minishell.exit_code = 127;
	}
}

static void	check_pid(t_cmd **command, pid_t pid[1024], int id)
{
	if (pid[id] == -1)
	{
		free_minishell();
		exit(11);
	}
	if (pid[id] == 0)
		child_execution(*command);
}

static void	child_execution(t_cmd *command)
{
	if (command->fd_in > 2)
		dup2(command->fd_in, STDIN_FILENO);
	if (command->fd_out > 2)
		dup2(command->fd_out, STDOUT_FILENO);
	close_all_fds();
	if (is_builtin_command(command))
		send_to_execution_in_child(command);
	else
	{
		execution_child_signals();
		execve(command->exec_path, command->exec, command->envp);
		execution_error(command->exec[0], errno);
	}
	free_minishell();
	exit(g_minishell.exit_code);
}

static void	command_execution(t_cmd **command)
{
	pid_t	pid[1024];
	int		id;

	id = -1;
	while (*command)
	{
		execution_parent_signals();
		count_quotes(*command, g_minishell.parser->input);
		expand_args(*command);
		(*command)->exec_path = get_command_path(*command);
		(*command)->envp = create_execution_envp();
		if ((*command)->fd_in == -1 || (*command)->fd_out == -1)
			execution_error((*command)->filename, (*command)->error_number);
		if ((*command)->exec_path && is_forked_command(*command))
		{
			pid[++id] = fork();
			check_pid(command, pid, id);
		}
		close_single_fd(*command, IN_OUT);
		*command = (*command)->next;
	}
	wait_pids(pid, id);
}
