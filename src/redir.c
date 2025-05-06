/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:38:43 by mecauchy          #+#    #+#             */
/*   Updated: 2025/05/07 00:52:06 by vluo             ###   ########.fr       */
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

void	init_fds(t_data *data)
{
	int	i;

	i = 0;
	data->fd = malloc(sizeof(int) * ((data->nb_cmds) * 2));
	if (!data->fd)
	{
		return ;
	}
	// if (data->nb_cmds == 1)
	// {
	// 	pipe(data->fd);
	// }
	// else
	// {
	while (i < data->nb_cmds - 1)
	{
		if (pipe(data->fd + i * 2) == -1)
		{
			perror("pipe");
			exit(1);
		}
		i++;
	}
	// }
}

void	close_fds(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmds - 1)
	{
		close(data->fd[i * 2]);
		close(data->fd[(i * 2) + 1]);
		i++;
	}
}

void	redirect_pipe(t_data *data, int i)
{
	if (i == 0)
	{
		dup2(data->fd[1], STDOUT_FILENO);
	}
	else if (i == data->nb_cmds - 1)
	{
		dup2(data->fd[(2 * i) - 2], STDIN_FILENO);
	}
	else
	{
		dup2(data->fd[(2 * i) - 2], STDIN_FILENO);
		dup2(data->fd[(2 * i) + 1], STDOUT_FILENO);
	}
	close_fds(data);
}

void	wait_all_pids(t_data *data, t_env_vars *vars, t_cmd *cmds)
{
	int	i;

	i = 0;
	while (i < data->nb_cmds)
	{
		wait_upex(data -> pid[i], vars, cmds->args[i]->arr);
		i++;
	}
}
