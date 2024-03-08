/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 00:44:01 by eisikogl          #+#    #+#             */
/*   Updated: 2024/03/08 16:23:01 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	validate_var_name(char *var_name)
{
	int	i;

	i = 0;
	if (ft_isdigit(var_name[i]))
		return (0);
	while (var_name[i])
	{
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	*search_env_value(char *var)
{
	t_envp	*ptr;

	ptr = g_minishell.envp;
	while (ptr != NULL)
	{
		if (strcmp_eq(var, ptr->key))
			return (ptr->value);
		ptr = ptr->next;
	}
	return (NULL);
}

int	get_envp_size(t_envp *envp_lst)
{
	int		count;
	t_envp	*tmp;

	count = 0;
	if (!envp_lst)
		return (0);
	tmp = envp_lst;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}
