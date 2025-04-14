/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:02:48 by vluo              #+#    #+#             */
/*   Updated: 2025/04/14 16:25:53 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_ctrc_c(int sig)
{
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	if (g_signal == 0)
		return (rl_redisplay());
	g_signal = sig;
}

struct sigaction	*init_ctrl_c_sig(void)
{
	struct sigaction	*sa;
	int					err;

	sa = ft_calloc(1, sizeof(struct sigaction));
	if (sa == NULL)
		return (NULL);
	sa -> sa_handler = handle_ctrc_c;
	sigemptyset(&(sa->sa_mask));
	err = sigaction(SIGINT, sa, NULL);
	if (err < 0)
		return (NULL);
	return (sa);
}
