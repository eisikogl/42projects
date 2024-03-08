/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 00:44:26 by eisikogl          #+#    #+#             */
/*   Updated: 2024/03/08 16:23:01 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	count_quotes(t_cmd *cmd, char *str)
{
	int		i;
	int		single_quotes;
	int		double_quotes;

	i = -1;
	single_quotes = 0;
	double_quotes = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == '\'')
			single_quotes++;
		if (str[i] == '\"')
			double_quotes++;
	}
	cmd->s_quotes = single_quotes;
	cmd->d_quotes = double_quotes;
}

void	expand_args(t_cmd *cmd)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (cmd->exec[++i])
	{
		if (cmd->s_quotes >= 2 && handle_quotes(cmd, "\'", i))
			continue ;
		if (cmd->d_quotes >= 2)
			handle_quotes(cmd, "\"", i);
		if (!(ft_strncmp(cmd->exec[i], "$", 2) == 0))
			handle_dollar_sign(cmd, tmp, i);
		handle_home(cmd, tmp, i);
	}
	cmd->argc = i;
}
