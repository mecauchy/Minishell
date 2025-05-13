/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:21:27 by vluo              #+#    #+#             */
/*   Updated: 2025/05/13 17:01:37 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

/* wait_upex manuel

wait and update exit selon la valeur de retour du processus
-> si il y a eu une erreur echo $? pour voir la valeur de sortie

Arguments : 
	- pid : l'id du process dont on veut wait
	- vars : les variables d'environnement
*/

void	wait_upex(int pid, t_env_vars *vars, char **cmd_args, int do_free)
{
	int		status;
	char	*exit_status;

	g_signal = SIGUSR1;
	waitpid(pid, &status, 0);
	if (g_signal == SIGINT)
		exit_status = ft_itoa(128 + g_signal);
	else if (WIFEXITED(status))
	{
		exit_status = ft_itoa(WEXITSTATUS(status));
		if (WEXITSTATUS(status) == 127)
			if (cmd_args)
				printf("%s: command not found\n", cmd_args[0]);
	}
	else
	{
		exit_status = ft_itoa(128 + g_signal);
		if (g_signal == SIGUSR1)
			exit_status = ft_itoa(128 + 3);
	}
	if (cmd_args)
		vars_add(vars, "_", cmd_args[0]);
	if (do_free)
		free_tab(cmd_args);
	return (vars_add(vars, "?", exit_status), free(exit_status));
}

char	*get_last_arg(char **cmd_arg, t_env_vars *vars)
{
	int	i;

	i = 0;
	while (cmd_arg[i + 1])
		i ++;
	return (expand(cmd_arg[i], vars));
}

long long	ft_atoll(char *nb)
{
	long long	res;
	int			i;
	long long	signe;

	i = 0;
	res = 0;
	signe = 1;
	while (nb[i] && (nb[i] == 32 || (nb[i] >= 8 && nb[i] <= 13)))
		i ++;
	if (nb[i] == 43 || nb[i] == 45)
	{
		if (nb[i] == 45)
			signe = -1;
		i ++;
	}
	while (nb[i] && (nb[i] >= 48 && nb[i] <= 57))
	{
		res = (res * 10) + (nb[i] - '0');
		i ++;
	}
	return (res * signe);
}
