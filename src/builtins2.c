/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:11:02 by vluo              #+#    #+#             */
/*   Updated: 2025/05/14 17:49:19 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_env(char *name, char *value)
{
	write(1, name, ft_strlen(name));
	write(1, "=", 1);
	write(1, value, ft_strlen(value));
	write(1, "\n", 1);
}

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
	write(2, "bash: export: ", 14);
	write(2, arg, ft_strlen(arg));
	write(2, ": not a valid identifier\n", 25);
	return (free(name), free(value), 0);
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

void	exit_too_many_args(char **cmd_args, t_mini *mini)
{
	int		i;
	char	*cmds[2];

	i = 0;
	while (cmd_args[i] && i < 4)
		i ++;
	if (i >= 3)
	{
		write(2, "bash: exit: too many arguments\n", 31);
		cmds[0] = "exit";
		cmds[1] = "1";
		return (ft_exit(cmds, mini));
	}
	return (ft_exit(cmd_args, mini));
}

int	is_builtin(char *cmd, char **cmd_args, t_mini *mini)
{
	int	i;

	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (ft_pwd(mini -> env_vars), 1);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (ft_env(mini -> env_vars), 1);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (ft_export(cmd_args, mini -> env_vars), 1);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (ft_unset(cmd_args, mini -> env_vars), 1);
	else if (ft_strncmp(cmd, "echo", 5) == 0)
		return (ft_echo(cmd_args, mini -> env_vars), 1);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
	{
		i = 0;
		while (cmd_args[i] && i < 4)
			i ++;
		if (i >= 3)
			return (write(2, "bash: cd: too many arguments\n", 29),
				vars_add(mini->env_vars, "?", "1"), 1);
		return (ft_cd(cmd_args[1], mini -> env_vars), 1);
	}
	return (0);
}
