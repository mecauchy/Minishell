/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:02:48 by vluo              #+#    #+#             */
/*   Updated: 2025/05/13 17:03:45 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sigint(int sig)
{
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	if (g_signal == 0 || g_signal == SIGUSR2)
	{
		g_signal = SIGUSR2;
		return (rl_redisplay());
	}
	g_signal = sig;
}

void	handle_sigquit(int sig)
{
	write(2, "Quit (core dumped) \n", 20);
	rl_replace_line("", 0);
	rl_on_new_line();
	g_signal = sig;
}

struct sigaction	**init_sigs(void)
{
	struct sigaction	**sas;
	int					err;

	sas = ft_calloc(2, sizeof(struct sigaction *));
	if (!sas)
		return (NULL);
	sas[0] = ft_calloc(1, sizeof(struct sigaction));
	sas[1] = ft_calloc(1, sizeof(struct sigaction));
	if (!sas[0] || !sas[1])
		return (free(sas), NULL);
	sas[0]->sa_handler = handle_sigint;
	sigemptyset(&(sas[0]->sa_mask));
	err = sigaction(SIGINT, sas[0], NULL);
	if (err < 0)
		return (free(sas), NULL);
	sas[1]->sa_handler = handle_sigquit;
	sigemptyset(&(sas[1]->sa_mask));
	err = sigaction(SIGQUIT, sas[1], NULL);
	if (err < 0)
		return (free(sas[0]), free(sas), NULL);
	return (sas);
}
