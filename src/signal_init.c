/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:06:52 by vluo              #+#    #+#             */
/*   Updated: 2025/03/31 12:27:08 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

struct sigaction	**init_signals(void)
{
	struct sigaction	**sas;

	sas = malloc(sizeof(struct sigaction *) * 5);
	sas[4] = 0;
	sas[0] = init_sa(SIGUSR1, handle_usr1, SA_SIGINFO);
	sas[1] = init_sa(SIGUSR2, handle_usr2, SA_SIGINFO);
	sas[2] = init_sa(SIGINT, handle_ctrc_c, -1);
	sas[3] = init_sa(SIGCHLD, handle_chld, -1);
	if (!sas[0] || !sas[1] || !sas[2] || !sas[3])
		return (free(sas[0]), free(sas[1]), free(sas[2]), free(sas[3]), NULL);
	return (sas);
}
