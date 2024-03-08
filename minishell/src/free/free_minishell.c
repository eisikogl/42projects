/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 00:44:33 by eisikogl          #+#    #+#             */
/*   Updated: 2024/03/08 16:23:01 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	free_execution_list(char **exec);
static void	free_envp(t_cmd *command);

void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

void	free_command(void)
{
	t_cmd	*cmd;
	t_cmd	*curr;

	curr = g_minishell.command;
	while (curr)
	{
		cmd = curr;
		curr = curr->next;
		free_tokens(&cmd->commands);
		free_tokens(&cmd->redirections);
		free_execution_list(cmd->exec);
		if (cmd->envp)
			free_envp(cmd);
		if (cmd->exec_path)
			free(cmd->exec_path);
		free(cmd);
	}
	g_minishell.command = NULL;
}

void	free_minishell(void)
{
	if (g_minishell.envp)
		free_env_lst(&g_minishell.envp);
	if (g_minishell.parser)
		free_parser();
	if (g_minishell.command)
		free_command();
	rl_clear_history();
}

static void	free_execution_list(char **exec)
{
	int	i;

	i = -1;
	if (!exec)
		return ;
	while (exec[++i])
		free(exec[i]);
	free(exec);
}

static void	free_envp(t_cmd *command)
{
	int	i;

	i = -1;
	while (command->envp[++i])
		free(command->envp[i]);
	free(command->envp);
	command->envp = NULL;
}
