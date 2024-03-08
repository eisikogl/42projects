/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 00:43:55 by eisikogl          #+#    #+#             */
/*   Updated: 2024/03/08 16:23:01 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	unset_error_msg(char *word);
static void	unset_env_var(t_envp **env_list, char *word);

int	unset_builtin(t_cmd *command)
{
	int		i;

	i = 1;
	while (command->exec[i] != NULL)
	{
		if (validate_var_name(command->exec[i]))
			unset_env_var(&g_minishell.envp, command->exec[i]);
		else
			unset_error_msg(command->exec[i]);
		i++;
	}
	return (0);
}

static int	unset_error_msg(char *word)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(word, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	g_minishell.exit_code = EXIT_FAILURE;
	return (g_minishell.exit_code);
}

static void	unset_env_var(t_envp **env_list, char *word)
{
	if (strcmp_eq((*env_list)->key, word))
		del_first_node(env_list);
	else
		del_node(env_list, word);
}
