/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_to_executer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 00:44:37 by eisikogl          #+#    #+#             */
/*   Updated: 2024/03/08 16:23:01 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void		set_command_endpoints(t_cmd **cmd, t_token **list, int *prev);
static size_t	get_lst_size(t_token *lst);
static char		**convert_to_array(t_token *token);
static void		create_execution_array(void);

void	set_commands(void)
{
	t_cmd	*command;
	t_token	*token_list;
	int		prev;
	int		id;

	token_list = g_minishell.parser->tokens;
	prev = -1;
	id = 0;
	while (token_list)
	{
		command = init_command(id);
		set_command_endpoints(&command, &token_list, &prev);
		command_add_back(command);
		id++;
	}
	create_execution_array();
}

static void	set_command_endpoints(t_cmd **cmd, t_token **list, int *prev)
{
	t_token	**location;	

	while (*list && (*list)->token_type < T_PIPE)
	{
		location = &(*cmd)->commands;
		if (is_redirection(*prev, (*list)->token_type))
			location = &(*cmd)->redirections;
		token_add_back(location, token_dup(*list));
		(*prev) = (*list)->token_type;
		(*list) = (*list)->next;
	}
	if (*list)
	{
		(*cmd)->endpoint = (*list)->token_type;
		(*prev) = (*list)->token_type;
		(*list) = (*list)->next;
	}
}

static size_t	get_lst_size(t_token *lst)
{
	size_t	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

static char	**convert_to_array(t_token *token)
{
	size_t	size;
	char	**array;
	int		i;

	size = get_lst_size(token) + 1;
	array = ft_calloc(sizeof(char *), size);
	if (!array)
	{
		free_minishell();
		exit(11);
	}
	i = 0;
	while (token)
	{
		array[i] = ft_strdup(token->token_value);
		token = token->next;
		i++;
	}
	return (array);
}

static void	create_execution_array(void)
{
	t_cmd	*command;

	command = g_minishell.command;
	while (command)
	{
		command->exec = convert_to_array(command->commands);
		command = command->next;
	}
}
