/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:11:02 by vluo              #+#    #+#             */
/*   Updated: 2025/04/14 16:49:10 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_export_one(char *arg, t_env_vars *vars)
{
	int		j;
	char	*name;
	char	*value;

	j = 0;
	while (arg[j] && arg[j] != '=')
		j ++;
	name = ft_substr(arg, 0, j);
	value = ft_substr(arg, j + 1, ft_strlen(arg) - j);
	if (!name || !value)
		return (free(name), free(value), 0);
	if (ft_is_identifier(name))
		return (vars_add(vars, name, value), free(name), free(value), 1);
	return (printf("export: not an identifier: %s\n", name),
		free(name), free(value), 0);
}

void	ft_export(char **args, t_env_vars *vars)
{
	int	i;
	int	exit;

	i = 0;
	exit = 0;
	while (args[++i])
		if (ft_export_one(args[i], vars) == 0)
			exit = 1;
	if (exit == 1)
		vars_add(vars, "?", "1");
	else
		vars_add(vars, "?", "0");
}

int	is_builtin(char *cmd, char **cmd_args, t_mini *mini)
{
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (ft_pwd(mini -> env_vars), 1);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (ft_env(mini -> env_vars), 1);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (ft_export(cmd_args, mini -> env_vars), 1);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (ft_unset(cmd_args, mini -> env_vars), 1);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (ft_exit(cmd_args, mini), 1);
	else if (ft_strncmp(cmd, "echo", 5) == 0)
		return (ft_echo(cmd_args, mini -> env_vars), 1);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (ft_cd(cmd_args[1], mini -> env_vars), 1);
	return (0);
}
