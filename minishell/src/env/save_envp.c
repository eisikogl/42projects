/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 00:44:03 by eisikogl          #+#    #+#             */
/*   Updated: 2024/03/08 16:23:01 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	export_error(char *variable);
static int	change_env_var(char *var_name, char *value);
static int	env_var_exists(char *var_name);
static int	save_only_name(char *variable);

int	save_env_var(char *variable, int validate)
{
	char	**split_var;
	char	*env_value;

	if (validate && *variable == '=')
		return (export_error(variable));
	if (ft_strchr(variable, '=') == NULL)
		return (save_only_name(variable));
	split_var = ft_split(variable, '=');
	if (split_var == NULL)
		return (0);
	if (validate && !validate_var_name(split_var[0]))
	{
		ft_matrix_free(&split_var);
		return (export_error(variable));
	}
	env_value = get_env_value(variable, split_var[0]);
	if (!change_env_var(split_var[0], env_value))
		env_lst_add_back(&g_minishell.envp, ft_strdup(split_var[0]),
			env_value, variable);
	ft_matrix_free(&split_var);
	return (1);
}

static int	export_error(char *variable)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("export", 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(variable, 2);
	ft_putstr_fd("': ", 2);
	ft_putendl_fd("not a valid identifier", 2);
	g_minishell.exit_code = 1;
	return (g_minishell.exit_code);
}

static int	change_env_var(char *var_name, char *value)
{
	t_envp	*envp;

	envp = g_minishell.envp;
	while (envp != NULL)
	{
		if (strcmp_eq(envp->key, var_name))
		{
			if (envp->value)
				free(envp->value);
			envp->value = value;
			return (1);
		}
		envp = envp->next;
	}
	return (0);
}

static int	env_var_exists(char *var_name)
{
	t_envp	*envp;

	envp = g_minishell.envp;
	while (envp != NULL)
	{
		if (strcmp_eq(envp->key, var_name))
			return (1);
		envp = envp->next;
	}
	return (0);
}

static int	save_only_name(char *variable)
{
	if (env_var_exists(variable))
		return (1);
	if (validate_var_name(variable))
	{
		env_lst_add_back(&g_minishell.envp,
			ft_strdup(variable), NULL, variable);
		return (1);
	}
	return (export_error(variable));
}
