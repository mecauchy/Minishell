/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:29:00 by vluo              #+#    #+#             */
/*   Updated: 2025/05/16 12:30:24 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(t_env_vars *vars)
{
	int		pid;
	char	*pw;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		g_signal = SIGUSR1;
		signal(SIGINT, SIG_DFL);
		pw = get_var_value(vars, "PWD");
		write(1, pw, ft_strlen(pw));
		write(1, "\n", 1);
		exit(0);
	}
	else
		wait_upex(pid, vars, ft_split("pwd", ' '), 1);
}

void	ft_env(t_env_vars *vars)
{
	int			pid;
	t_env_vars	*tmp;
	char		*value_;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid != 0)
		return (wait_upex(pid, vars, ft_split("env", ' '), 1));
	g_signal = SIGUSR1;
	signal(SIGINT, SIG_DFL);
	tmp = vars;
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp -> name, "_", 2))
			value_ = tmp -> value;
		if (ft_strncmp(tmp->name, "?", 2) && ft_strncmp(tmp->name, "_", 2))
			print_env(tmp -> name, tmp -> value);
		tmp = tmp -> next;
	}
	return (write(1, "_=", 2), write(1, value_, ft_strlen(value_)),
		write(1, "\n", 1), exit(0));
}

void	ft_unset(char **args, t_env_vars *vars)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		if (!ft_strncmp(args[i], "?", 2))
			break ;
		else
			vars_del_one(vars, args[i]);
	}
	vars_add(vars, "?", "0");
}

int	check_isll(char *nb, int len)
{
	int			i;
	long long	res;
	int			po;

	if (len > 20)
		return (0);
	po = 1;
	i = 0;
	while (nb[i] && (nb[i] == ' ' || nb[i] == '\t'))
		i ++;
	if (nb[i] == '-')
		po = -1;
	res = ft_atoll(nb);
	if (res < 0 && po == -1)
		return (1);
	if (res >= 0 && po == 1)
		return (1);
	return (0);
}

void	ft_exit(char **n, t_mini *mini)
{
	char		*exit;
	int			i;
	int			j;
	long long	res;

	if (n[1] == 0)
		return (mini->exit_status = ft_atoi(get_var_value(mini->env_vars,
					"?")), mini -> do_exit = 1, (void)n);
	exit = n[1];
	j = 0;
	while (exit[j] && (exit[j] == ' ' || exit[j] == '\t'))
		j ++;
	i = 0;
	if (exit[j] && (exit[j] == '-' || exit[j] == '+'))
		i ++;
	while (exit[i + j] && ft_isdigit(exit[i + j]))
		i ++;
	res = ft_atoll(exit);
	if (!check_isll(exit, i) || exit[i + j]
		|| res > LLONG_MAX || res < LLONG_MIN)
		return (write(2, "bash: exit: ", 12), write(2, exit, ft_strlen(exit)),
			write(2, ": numeric argument required\n", 28),
			mini -> exit_status = 2, mini -> do_exit = 1, (void)n);
	mini -> exit_status = res;
	mini -> do_exit = 1;
}
