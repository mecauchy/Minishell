/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:02:48 by vluo              #+#    #+#             */
/*   Updated: 2025/03/29 17:07:07 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_usr1(int sig, siginfo_t *info, void *p)
{
	g_signal = sig;
	kill(info->si_pid, SIGUSR2);
	(void)sig;
	(void)p;
}

void	handle_usr2(int sig, siginfo_t *info, void *p)
{
	g_signal = sig;
	while (g_signal != 2)
		(void)sig;
	kill(info->si_pid, SIGKILL);
	(void)p;
}

void	handle_ctrc_c(int sig)
{
	if (g_signal == 0)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_signal = 0;
		return ;
	}
	g_signal = sig;
}

void	handle_chld(int sig)
{
	g_signal = 2;
	(void)sig;
}
