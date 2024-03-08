/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 00:44:39 by eisikogl          #+#    #+#             */
/*   Updated: 2024/03/08 16:23:01 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_parser	*init_parser(void)
{
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
	if (!parser)
	{
		free_minishell();
		exit(12);
	}
	parser->input = NULL;
	parser->tokens = NULL;
	return (parser);
}

int	define_token_type(char *token)
{
	if (!ft_strncmp(token, "|", 1) && ft_strncmp(token, "||", 2))
		return (T_PIPE);
	if (!ft_strncmp(token, ">", 1) && ft_strncmp(token, ">>", 2))
		return (T_REDIR_OUT);
	if (!ft_strncmp(token, "<", 1) && ft_strncmp(token, "<<", 2))
		return (T_REDIR_IN);
	if (!ft_strncmp(token, ">>", 2))
		return (T_APPEND);
	if (!ft_strncmp(token, "<<", 2))
		return (T_HEREDOC);
	else
		return (T_WORD);
}
