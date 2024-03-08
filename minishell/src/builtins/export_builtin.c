/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 00:43:50 by eisikogl          #+#    #+#             */
/*   Updated: 2024/03/08 16:23:01 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	put_export(int fd);

int	export_builtin(t_cmd *command)
{
	int		i;
	int		result;
	int		error;

	i = 1;
	error = 0;
	if (command->exec[i] == NULL)
	{
		put_export(command->fd_out);
		return (0);
	}
	while (command->exec[i])
	{
		result = save_env_var(command->exec[i], 1);
		if (!error && !result)
			error = 1;
		i++;
	}
	if (error)
		g_minishell.exit_code = 1;
	else
		g_minishell.exit_code = 0;
	return (g_minishell.exit_code);
}

static void	put_export(int fd)
{
	t_envp	*envp;

	envp = g_minishell.envp;
	while (envp != NULL)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(envp->key, fd);
		if (envp->value)
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(envp->value, fd);
			ft_putendl_fd("\"", fd);
		}
		else
			ft_putstr_fd("\n", fd);
		envp = envp->next;
	}
}
