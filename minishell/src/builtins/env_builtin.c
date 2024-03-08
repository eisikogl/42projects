/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 00:43:46 by eisikogl          #+#    #+#             */
/*   Updated: 2024/03/08 16:23:01 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	put_env(void);

int	env_builtin(t_cmd *command)
{
	int	i;

	i = 1;
	if (command->exec[i] && ft_strchr(command->exec[i], '=') == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command->exec[i], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free_minishell();
		free(g_minishell.command->exec_path);
		g_minishell.exit_code = 127;
		exit(g_minishell.exit_code);
		return (1);
	}
	while (command->exec[i])
	{
		if (*command->exec[i] != '=')
			save_env_var(command->exec[i], 0);
		else
			ft_putendl_fd(command->exec[i], 1);
		i++;
	}
	put_env();
	return (0);
}

static void	put_env(void)
{
	t_envp	*envp;

	envp = g_minishell.envp;
	while (envp != NULL)
	{
		if (envp->value)
		{
			ft_putstr_fd(envp->key, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(envp->value, 1);
		}
		envp = envp->next;
	}
}
