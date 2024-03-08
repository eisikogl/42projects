/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 00:44:19 by eisikogl          #+#    #+#             */
/*   Updated: 2024/03/08 16:23:01 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	heredoc_error(int *fd);
static void	heredoc_display_error(char *limiter);
static void	heredoc_loop(char *limiter, int *fd);

int	heredoc(char *filename)
{
	int	fd[2];
	int	pid;
	int	status;

	if (pipe(fd) == -1)
		return (heredoc_error(NULL));
	pid = fork();
	if (pid == -1)
		return (heredoc_error(NULL));
	if (!pid)
	{
		close(fd[0]);
		heredoc_loop(ft_strdup(filename), &fd[1]);
	}
	heredoc_parent_signal();
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		return (heredoc_error(fd));
	return (fd[0]);
}

static int	heredoc_error(int *fd)
{
	if (fd)
		close(fd[0]);
	else
	{
		free_minishell();
		exit(1);
	}
	return (-1);
}

static void	heredoc_display_error(char *limiter)
{
	ft_putstr_fd("minishell: warning: here-document delimited by ", 2);
	ft_putstr_fd("end of file (wante", 2);
	ft_putstr_fd(limiter, 2);
	ft_putstr_fd(")\n", 2);
}

static void	heredoc_loop(char *limiter, int *fd)
{
	char	*line;
	int		size;

	heredoc_child_signal();
	line = readline("> ");
	size = ft_strlen(limiter);
	while (!0)
	{
		if (!line)
			heredoc_display_error(limiter);
		if (!line || (!ft_strncmp(limiter, line, size) && !line[size]))
			break ;
		ft_putendl_fd(line, *fd);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(*fd);
	(free(limiter), exit(1));
}
