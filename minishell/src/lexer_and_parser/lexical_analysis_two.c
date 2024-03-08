/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis_two.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 00:44:44 by eisikogl          #+#    #+#             */
/*   Updated: 2024/03/08 16:23:01 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_closed_quotation_mark(t_token *token);
static int	is_valid_redirection(t_token *token);
static int	is_valid_pipe(t_token *token, int pos);
static int	check_bash_grammar(void);

int	is_valid_command(void)
{
	if (check_bash_grammar())
	{
		set_commands();
		return (1);
	}
	return (0);
}

static int	is_closed_quotation_mark(t_token *token)
{
	int		flag;
	int		i;

	flag = -1;
	i = 0;
	if (!token->next)
	{
		while (token->token_value[i])
		{
			if (flag == -1 && (token->token_value[i] == 34
					|| token->token_value[i] == 39))
				flag = i;
			else if (flag != -1
				&& token->token_value[i] == token->token_value[flag])
				flag = -1;
			i++;
		}
		if (flag != -1)
		{
			ft_putstr_fd("minishell: found EOF when expecting quote\n", 2);
			return (0);
		}
	}
	return (1);
}

static int	is_valid_redirection(t_token *token)
{
	if (token->token_type == T_REDIR_IN
		|| token->token_type == T_APPEND
		|| token->token_type == T_REDIR_OUT || token->token_type == T_HEREDOC)
	{
		if (!token->next)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
			ft_putstr_fd("`newline'\n", 2);
			return (0);
		}
		else if (token->next->token_type != T_WORD)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token: ", 2);
			ft_putstr_fd(token->next->token_value, 2);
			ft_putstr_fd("\n", 2);
			return (0);
		}
	}
	return (1);
}

static int	is_valid_pipe(t_token *token, int pos)
{
	if (token->token_type == T_PIPE)
	{
		if (pos == 0 || !token->next)
		{
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
			return (0);
		}
	}
	return (1);
}

static int	check_bash_grammar(void)
{
	t_token	*token;
	int		index;

	token = g_minishell.parser->tokens;
	index = 0;
	while (token)
	{
		if (!is_valid_pipe(token, index) || !is_valid_redirection(token)
			|| !is_closed_quotation_mark(token))
			return (0);
		token = token->next;
		index++;
	}
	return (1);
}
