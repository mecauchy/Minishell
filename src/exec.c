/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mecauchy <mecauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:38:43 by mecauchy          #+#    #+#             */
/*   Updated: 2025/04/09 14:53:13 by mecauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_pids(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmds)
	{
		data->pid[i] = -1;
		i++;
	}
}

// pas fini a revoir
void	init_nb_fork(t_data *data)
{
	int	i;

	i = 0;
	data->fd = malloc(sizeof(int) * ((data->nb_cmds - 1) * 2));
	if (data->fd)
		ft_error();
	while (i < data->nb_cmds)
	{
		if (pipe(data->fd + i * 2))
			ft_error();
		i++;
	}
}

void	exec_multi_cmd(t_data *data)
{
	int	i;

	i = 0;
	while (i > data->nb_cmds)
	{
		data->pid[i] = fork();
		if (data->pid[i])
		{
			child_exec(data);
		}
		if (data->pid[i] < 0)
		{
			ft_error();
		}
	}
}