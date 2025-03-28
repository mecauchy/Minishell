/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:02:48 by vluo              #+#    #+#             */
/*   Updated: 2025/03/28 17:24:51 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_usr1(int sig, siginfo_t *info, void *p)
{
	g_signal = sig;
	kill(info->si_pid, SIGUSR2);
	p++;
}

void	handle_usr2(int sig, siginfo_t *info, void *p)
{
	while (g_signal != 2)
		(void)sig;
	kill(info->si_pid, SIGTERM);
	p ++;
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
	write(2, "\n", 1);
	g_signal = sig;
}

struct sigaction	*init_sa(int sig, void *handler, int flags)
{
	struct sigaction	*sa;
	int					err;

	sa = malloc(sizeof(struct sigaction));
	ft_memset(sa, 0, sizeof(struct sigaction));
	if (flags == -1)
		sa -> sa_handler = handler;
	else
		sa -> sa_sigaction = handler;
	sigemptyset(&(sa->sa_mask));
	if (flags != -1)
		sa -> sa_flags = flags;
	err = sigaction(sig, sa, NULL);
	if (err < 0)
		return (NULL);
	return (sa);
}

struct sigaction	**init_sas(void)
{
	struct sigaction	**sas;

	sas = malloc(sizeof(struct sigaction *) * 4);
	sas[3] = 0;
	sas[0] = init_sa(SIGUSR1, handle_usr1, SA_SIGINFO);
	sas[1] = init_sa(SIGUSR2, handle_usr2, SA_SIGINFO);
	sas[2] = init_sa(SIGINT, handle_ctrc_c, -1);
	if (!sas[0] || !sas[1] || !sas[2])
		return (free(sas[0]), free(sas[1]), free(sas[2]), NULL);
	return (sas);
}
