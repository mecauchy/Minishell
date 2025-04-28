/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:29:00 by vluo              #+#    #+#             */
/*   Updated: 2025/04/28 19:29:57 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(t_env_vars *vars)
{
	ft_printf("%s\n", get_var_value(vars, "PWD"));
	vars_add(vars, "?", "0");
}

void	ft_env(t_env_vars *vars)
{
	t_env_vars	*tmp;
	char		*value_;

	vars_add(vars, "?", "0");
	tmp = vars;
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp -> name, "_", 2))
			value_ = tmp -> value;
		if (ft_strncmp(tmp -> name, "?", 2) && ft_strncmp(tmp -> name, "_", 2))
			ft_printf("%s=%s\n", tmp -> name, tmp -> value);
		tmp = tmp -> next;
	}
	ft_printf("_=%s\n", value_);
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
	if (res <= 0 && po == -1)
		return (1);
	if (res > 0 && po == 1)
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
		return (printf("bash: exit: %s: numeric argument requiered\n",
				exit), mini -> exit_status = 2, mini -> do_exit = 1, (void)n);
	mini -> exit_status = res;
	mini -> do_exit = 1;
}
