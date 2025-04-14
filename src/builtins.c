/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:29:00 by vluo              #+#    #+#             */
/*   Updated: 2025/04/14 13:30:29 by vluo             ###   ########.fr       */
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

void	ft_exit(char **n, t_mini *mini)
{
	char	*exit_stat;

	if (n[1] == 0)
		exit_stat = get_var_value(mini -> env_vars, "?");
	else
		exit_stat = n[1];
	mini -> exit_status = ft_atoi(exit_stat);
}

void	ft_unset(char **args, t_env_vars *vars)
{
	int	i;
	int	exit;

	i = -1;
	while (args[++i])
	{
		if (!ft_strncmp(args[i], "?", 2))
		{
			printf("unset: no matched found: ?\n");
			exit = 1;
		}
		else
			vars_del_one(vars, args[i]);
	}
	if (exit)
		vars_add(vars, "?", "1");
	else
		vars_add(vars, "?", "0");
}
