/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:29:47 by vluo              #+#    #+#             */
/*   Updated: 2025/05/16 13:54:18 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	echo_print(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		ft_putchar_fd(line[i], 1);
	return (1);
}

static int	echo_ch(char **args)
{
	int		i;

	if (!args[1])
		return (ft_putchar_fd('\n', 1), 0);
	if (!ft_strncmp(args[1], "-n", 3) && !args[2])
		return (0);
	if (!ft_strncmp(args[1], "-n", 3))
		i = 1;
	else
		i = 0;
	while (args[++i + 1])
	{
		if (!echo_print(args[i]))
			return (0);
		ft_putchar_fd(' ', 1);
	}
	if (!echo_print(args[i]))
		return (0);
	if (ft_strncmp(args[1], "-n", 3))
		ft_putchar_fd('\n', 1);
	return (0);
}

void	ft_echo(char **args, t_env_vars *vars)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		g_signal = SIGUSR1;
		signal(SIGINT, SIG_DFL);
		exit(echo_ch(args));
	}
	wait_upex(pid, vars, ft_split("echo", ' '), 1);
}
