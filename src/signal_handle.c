/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:02:48 by vluo              #+#    #+#             */
/*   Updated: 2025/03/30 19:34:48 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_usr1(int sig, siginfo_t *info, void *p)
{
	g_signal = sig;
	kill(info->si_pid, SIGUSR2);
	(void)p;
}

void	handle_usr2(int sig, siginfo_t *info, void *p)
{
	g_signal = sig;
	while (g_signal != SIGINT)
		continue ;
	kill(info->si_pid, SIGKILL);
	(void)p;
}

void	handle_ctrc_c(int sig)
{
	if (g_signal == 0)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	else if (g_signal == SIGUSR1)
	{
		g_signal = sig;
	}
	else if (g_signal == SIGUSR2)
	{
		write(2, "\n", 1);
		g_signal = sig;
	}
}

void	handle_chld(int sig)
{
	g_signal = SIGINT;
	(void)sig;
}
