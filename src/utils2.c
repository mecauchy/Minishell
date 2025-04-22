/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:21:27 by vluo              #+#    #+#             */
/*   Updated: 2025/04/21 14:50:13 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdatomic.h>

int	is_all_space(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (!((8 <= line[i] && line[i] <= 13) || line[i] == 32))
			return (0);
	return (1);
}

int	ft_is_identifier(char *name)
{
	int	i;

	if (!name)
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 0;
	while (name[++i])
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
	return (1);
}

void	wait_upex(int pid, t_env_vars *vars)
{
	int		status;
	char	*exit_status;

	g_signal = SIGUSR1;
	waitpid(pid, &status, 0);
	if (g_signal == SIGINT)
		exit_status = ft_itoa(128 + g_signal);
	else if (WIFEXITED(status))
		exit_status = ft_itoa(WEXITSTATUS(status));
	else
		exit_status = ft_itoa(128 + g_signal);
	vars_add(vars, "?", exit_status);
	free(exit_status);
}

char	*get_last_arg(char **cmd_arg, t_env_vars *vars)
{
	int	i;

	i = 0;
	while (cmd_arg[i + 1])
		i ++;
	return (expand(cmd_arg[i], vars));
}
