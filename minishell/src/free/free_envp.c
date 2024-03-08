/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 00:44:29 by eisikogl          #+#    #+#             */
/*   Updated: 2024/03/08 16:23:01 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	del_node(t_envp **env_list, char *word)
{
	t_envp	*temp;
	t_envp	*aux;

	temp = *env_list;
	while (temp != NULL && temp->next != NULL)
	{
		if (strcmp_eq(temp->next->key, word))
		{
			aux = temp->next;
			temp->next = aux->next;
			free(aux->key);
			free(aux->value);
			free(aux);
		}
		temp = temp->next;
	}
}

void	del_first_node(t_envp **env_list)
{
	t_envp	*temp;

	free((*env_list)->key);
	free((*env_list)->value);
	temp = (*env_list)->next;
	free(*env_list);
	*env_list = temp;
}

void	ft_matrix_free(char ***matrix)
{
	int	i;

	i = 0;
	if (!(*matrix))
		return ;
	while ((*matrix)[i])
	{
		free((*matrix)[i]);
		i++;
	}
	free(*matrix);
	*matrix = NULL;
	return ;
}

void	free_env_lst(t_envp **env_list)
{
	if (*env_list == NULL)
		return ;
	while (*env_list != NULL)
	{
		del_first_node(env_list);
	}
	*env_list = NULL;
}
