/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:21:27 by vluo              #+#    #+#             */
/*   Updated: 2025/05/16 13:26:34 by vluo             ###   ########.fr       */
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

int	check_is_main_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	return (0);
}
