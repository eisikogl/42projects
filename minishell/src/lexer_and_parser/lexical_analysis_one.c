/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis_one.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 00:44:42 by eisikogl          #+#    #+#             */
/*   Updated: 2024/03/08 16:23:01 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	has_matching_quote(const char *input, size_t index);

int	is_redirection(int prev, int token_type)
{
	if (token_type == T_REDIR_OUT || token_type == T_HEREDOC
		|| token_type == T_REDIR_IN || token_type == T_APPEND
		|| prev == T_REDIR_IN || prev == T_REDIR_OUT
		|| prev == T_APPEND || prev == T_HEREDOC)
		return (1);
	return (0);
}

int	is_valid_token(const char *input, size_t index, size_t prev)
{
	if (!index || !input[index])
		return (1);
	if (has_matching_quote(input, index))
		return (0);
	if (ft_strchr("|<> ", input[index]))
	{
		if (index - prev == 1)
		{
			if ((input[index] == '<' && input[prev] == '<')
				|| (input[index] == '>' && input[prev] == '>')
				|| (input[index] == ' ' && input[prev] == ' '))
				return (0);
		}
		if (ft_isblank(input[index]) && ft_isblank(input[index - 1]))
			return (0);
		return (1);
	}
	if (index > 0 && ft_strchr("|<> ", input[index - 1]))
		return (1);
	return (0);
}

static int	has_matching_quote(const char *input, size_t index)
{
	int		match;
	int		count;

	match = -1;
	count = 0;
	while (count < (int)index)
	{
		if ((input[count] == 34) || (input[count] == 39))
		{
			if (match == -1)
				match = (int)count;
			else if (match != -1 && input[match] == input[count])
				match = -1;
		}
		count++;
	}
	if (match != -1)
		return (1);
	return (0);
}
