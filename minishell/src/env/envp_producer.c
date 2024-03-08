/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_producer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 00:43:58 by eisikogl          #+#    #+#             */
/*   Updated: 2024/03/08 16:23:01 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**create_execution_envp(void)
{
	t_envp	*envp;
	char	**ret;
	size_t	i;
	size_t	size;

	envp = g_minishell.envp;
	i = 0;
	size = get_envp_size(envp);
	ret = (char **)malloc(sizeof(char *) * (size + 1));
	while (i < size)
	{
		ret[i++] = ft_strdup((char *)envp->fullstr);
		envp = envp->next;
	}
	ret[i] = 0;
	return (ret);
}

char	*get_env_value(char *envp, char *key)
{
	int		key_len;
	int		value_len;
	char	*value;

	if (!envp && !key)
		return (NULL);
	key_len = ft_strlen(key) + 1;
	value_len = ft_strlen(envp + key_len);
	value = ft_substr(envp, key_len, value_len);
	return (value);
}

int	env_lst_add_back(t_envp **env_list, char *name, char *value, char *fullstr)
{
	t_envp	*new_envp;
	t_envp	*temp;

	if (!name)
		return (EXIT_FAILURE);
	new_envp = (t_envp *)malloc(sizeof(t_envp));
	if (!new_envp)
		return (EXIT_FAILURE);
	new_envp->key = name;
	new_envp->value = value;
	new_envp->fullstr = fullstr;
	new_envp->next = NULL;
	if ((*env_list) == NULL)
		*env_list = new_envp;
	else
	{
		temp = *env_list;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_envp;
	}
	return (EXIT_SUCCESS);
}

void	set_envp(char **envp)
{
	int		i;
	char	**split_env;

	i = 0;
	while (envp[i])
	{
		split_env = ft_split(envp[i], '=');
		if (split_env[0] != NULL)
		{
			env_lst_add_back(&g_minishell.envp, ft_strdup(split_env[0]),
				get_env_value(envp[i], split_env[0]), envp[i]);
		}
		ft_matrix_free(&split_env);
		i++;
	}
	return ;
}
