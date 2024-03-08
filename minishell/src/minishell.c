/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 00:44:58 by eisikogl          #+#    #+#             */
/*   Updated: 2024/03/08 16:23:01 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_minishell	g_minishell;

static void	shell_loop(void);

int	main(int argc, char **argv, char **envp)
{
	if (argc > 1 || argv[1])
	{
		ft_putstr_fd("argc! \n", 2);
		return (1);
	}
	set_envp(envp);
	g_minishell.parser = NULL;
	g_minishell.command = NULL;
	g_minishell.exit_code = 0;
	shell_loop();
}

static void	shell_loop(void)
{
	while (!0)
	{
		shell_loop_signal();
		free_parser();
		free_command();
		g_minishell.parser = init_parser();
		g_minishell.parser->input = readline("minishell> ");
		if (!g_minishell.parser->input)
		{
			ft_putstr_fd("exit!\n", 2);
			free_minishell();
			exit(0);
		}
		add_history(g_minishell.parser->input);
		if (!tokenize_everything())
			continue ;
		execution_phase();
	}
}
