/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_signals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 00:44:51 by eisikogl          #+#    #+#             */
/*   Updated: 2024/03/08 16:23:01 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	execution_signal_handler(int signal);
static void	interrupt_handler(int signal);
static void	quit_handler(int signal);

void	execution_child_signals(void)
{
	signal(SIGINT, interrupt_handler);
	signal(SIGQUIT, quit_handler);
}

void	execution_parent_signals(void)
{
	signal(SIGQUIT, execution_signal_handler);
	signal(SIGINT, execution_signal_handler);
}

static void	execution_signal_handler(int signal)
{
	if (signal == SIGQUIT)
	{
		ft_putstr_fd("Quit\n", 2);
		g_minishell.exit_code = 131;
	}
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		g_minishell.exit_code = 130;
	}
}

static void	interrupt_handler(int signal)
{
	(void)signal;
	free_minishell();
	exit(130);
}

static void	quit_handler(int signal)
{
	(void)signal;
	free_minishell();
	exit(131);
}
