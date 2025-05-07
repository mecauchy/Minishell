/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:29:47 by vluo              #+#    #+#             */
/*   Updated: 2025/05/07 16:25:14 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_char_value(char *line, char esc)
{
	int	i;
	int	stop;

	i = 0;
	if (esc == '0')
	{
		while (i < 3 && line[i + 1]
			&& (line[i + 1] >= '0' && line[i + 1] <= '8'))
			i ++;
		ft_putchar_fd(octal_to_dec(ft_substr(line, 1, i)), 1);
		return (i + 1);
	}
	stop = 8;
	if (esc == 'x')
		stop = 2;
	if (esc == 'u')
		stop = 4;
	while (i < stop && line[i + 1]
		&& ((line[i + 1] >= 'A' && line[i + 1] <= 'F')
			|| (line[i + 1] >= '0' && line[i + 1] <= '9')))
		i ++;
	ft_putchar_fd(hex_to_dec(ft_substr(line, 1, i)), 1);
	return (i + 1);
}

static int	print_esc_char(char *line, char esc)
{
	if (esc == 'a')
		return (ft_putchar_fd('\a', 1), 1);
	if (esc == 'b')
		return (ft_putchar_fd('\b', 1), 1);
	if (esc == 'e')
		return (ft_putchar_fd('\e', 1), 1);
	if (esc == 'E')
		return (ft_putchar_fd('\E', 1), 1);
	if (esc == 'f')
		return (ft_putchar_fd('\f', 1), 1);
	if (esc == 'n')
		return (ft_putchar_fd('\n', 1), 1);
	if (esc == 'r')
		return (ft_putchar_fd('\r', 1), 1);
	if (esc == 't')
		return (ft_putchar_fd('\t', 1), 1);
	if (esc == 'v')
		return (ft_putchar_fd('\v', 1), 1);
	if (esc == '\\')
		return (ft_putchar_fd('\\', 1), 1);
	return (get_char_value(line, esc));
}

static int	echo_print(char *line)
{
	char	*esc_char;
	int		j;
	int		i;

	esc_char = "abceEfnrtv\\0xuU";
	i = -1;
	while (line[++i])
	{
		if (line[i] == '\\')
		{
			if (!line[i + 1])
				break ;
			j = -1;
			while (esc_char[++j])
				if (line[i + 1] == esc_char[j])
					break ;
			if (esc_char[j] && esc_char[j] == 'c')
				return (0);
			if (esc_char[j])
				i += print_esc_char(&line[i + 1], esc_char[j]);
		}
		else
			ft_putchar_fd(line[i], 1);
	}
	return (1);
}

static int	echo_ch(char **args, t_env_vars *vars)
{
	int		i;
	char	*line;

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
		line = expand(args[i], vars);
		if (!echo_print(line))
			return (free(line), 0);
		ft_putchar_fd(' ', 1);
		free(line);
	}
	line = expand(args[i], vars);
	if (!echo_print(line))
		return (free(line), 0);
	if (ft_strncmp(args[1], "-n", 3))
		ft_putchar_fd('\n', 1);
	return (free(line), 0);
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
		exit(echo_ch(args, vars));
	}
	else
		wait_upex(pid, vars, ft_split("echo", ' '), 1);
}
