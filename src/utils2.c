/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:21:27 by vluo              #+#    #+#             */
/*   Updated: 2025/03/31 12:24:11 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_sas(struct sigaction **sas)
{
	int	i;

	i = -1;
	while (sas[++i])
		free(sas[i]);
	free(sas);
}

void	update_exit_status(t_env_vars *vars, char *status)
{
	t_env_vars	*tmp;

	tmp = vars;
	while (tmp -> next != 0)
		tmp = tmp -> next;
	free(tmp -> value);
	tmp -> value = status;
}

int	is_all_space(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (!((8 <= line[i] && line[i] <= 13) || line[i] == 32))
			return (0);
	return (1);
}
