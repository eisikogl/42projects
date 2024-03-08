/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 00:44:24 by eisikogl          #+#    #+#             */
/*   Updated: 2024/03/08 16:23:01 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	handle_status(t_cmd *cmd, int i)
{
	if (cmd->exec[i][1] == '?'
		&& cmd->exec[i][2] == '\0')
	{
		free(cmd->exec[i]);
		cmd->exec[i] = ft_itoa(g_minishell.exit_code);
		return (1);
	}
	return (0);
}

int	handle_quotes(t_cmd *cmd, char *arg, int i)
{
	char	*token;

	token = ft_strchr(cmd->exec[i], *arg);
	if (token != NULL)
	{
		while (token != NULL)
		{
			ft_memmove(token, token + 1, ft_strlen(token));
			token = ft_strchr(cmd->exec[i], *arg);
		}
		return (1);
	}
	return (0);
}

void	handle_dollar_sign(t_cmd *cmd, char *tmp, int i)
{
	size_t	len;
	char	*token;

	len = ft_strlen(cmd->exec[i]);
	token = ft_strchr(cmd->exec[i], '$');
	if (token != NULL)
	{
		if (handle_status(cmd, i))
			return ;
		tmp = search_env_value(++token);
		if (tmp)
		{
			free(cmd->exec[i]);
			cmd->exec[i] = ft_strdup(tmp);
		}
		else if (len == 1)
			return ;
		else
		{
			free(cmd->exec[i]);
			cmd->exec[i] = ft_strdup("");
		}
	}
}

void	handle_home(t_cmd *cmd, char *tmp, int i)
{
	char	*sign_start;
	char	*tmp_arg;

	if (ft_strchr(cmd->exec[i], '~') != NULL)
	{
		tmp_arg = ft_strdup(cmd->exec[i]);
		sign_start = ft_strchr(tmp_arg, '~');
		tmp = search_env_value("HOME");
		free(cmd->exec[i]);
		if (++sign_start != NULL)
			cmd->exec[i] = ft_strjoin(tmp, sign_start);
		else
			cmd->exec[i] = ft_strdup(tmp);
		free(tmp_arg);
	}
}
