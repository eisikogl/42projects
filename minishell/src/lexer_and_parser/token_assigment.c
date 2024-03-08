/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_assigment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 00:44:46 by eisikogl          #+#    #+#             */
/*   Updated: 2024/03/08 16:23:01 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*token_dup(t_token *src)
{
	t_token	*dest;

	dest = malloc(sizeof(t_token));
	if (!dest)
	{
		free_minishell();
		exit(11);
	}
	dest->token_value = ft_strdup(src->token_value);
	dest->token_type = src->token_type;
	dest->next = NULL;
	return (dest);
}

t_token	*create_new_token(char *token_value, int is_sig)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		free_minishell();
		exit(12);
	}
	token->token_value = token_value;
	if (!is_sig)
		token->token_type = define_token_type(token_value);
	else
		token->token_type = T_WORD;
	token->next = NULL;
	return (token);
}

void	token_add_back(t_token **token, t_token *new_token)
{
	t_token	*node;

	node = *token;
	if (!node)
		(*token) = new_token;
	else
	{
		while (node->next)
			node = node->next;
		node->next = new_token;
	}
}

static void	token_list_creator(const char *input, size_t size)
{
	t_token	*token_list;
	char	*token_value;

	while (ft_isblank(*input))
	{
		size--;
		input++;
	}
	if (!size || !(*input))
		return ;
	token_value = ft_strndup(input, size);
	token_list = create_new_token(token_value, 0);
	token_add_back(&g_minishell.parser->tokens, token_list);
}

int	tokenize_everything(void)
{
	char	*input;
	size_t	index;
	size_t	prev;
	size_t	next;
	size_t	size;

	input = g_minishell.parser->input;
	index = 0;
	prev = index;
	next = index;
	size = 0;
	while (1)
	{
		if (is_valid_token(input, index, prev))
			next = index;
		size = next - prev;
		if (size > 0)
			token_list_creator(&input[prev], size);
		if (!input[index])
			break ;
		prev = next;
		index++;
	}
	return (is_valid_command());
}
