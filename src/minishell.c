/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:07:38 by vluo              #+#    #+#             */
/*   Updated: 2025/04/14 17:15:46 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal;

void	exec_cmd(char *cmd, char **cmd_args, t_env_vars *vars)
{
	int		pid;
	int		status;
	char	*exit_status;

	pid = fork();
	if (pid < 0)
		return (perror("Error: "));
	if (pid > 0)
	{
		g_signal = SIGUSR1;
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			exit_status = ft_itoa(WEXITSTATUS(status));
		else
			exit_status = ft_itoa(128 + g_signal);
		vars_add(vars, "?", exit_status);
		free(exit_status);
	}
	else
	{
		execve(cmd, cmd_args, get_envp(vars));
		return (perror("Error:"));
	}
}

void	exec_cmds(char *path_cmd, char **cmd_args, t_mini *mini)
{
	char	**paths;
	char	*cmd;
	int		i;

	paths = ft_split(path_cmd, '/');
	if (paths == 0)
		return ;
	i = 0;
	while (paths[i])
		i ++;
	cmd = paths[i - 1];
	vars_add(mini -> env_vars, "_", path_cmd);
	if (!is_builtin(cmd, cmd_args, mini))
		exec_cmd(path_cmd, cmd_args, mini -> env_vars);
	free_tab(paths);
}

void	parse_line(char *line, t_mini *mini)
{
	char	**full_cmd;
	char	*expa;
	char	*cmd;
	char	**cmd_args;

	full_cmd = split_cmds(line);
	expa = expand(full_cmd[0], mini -> env_vars);
	if (expa == NULL || !expa[0])
		return (free_tab(full_cmd), free(expa));
	cmd = get_correct_cmd(expa);
	if (cmd == NULL)
	{
		vars_add(mini -> env_vars, "?", "127");
		if (expa[0] && expa[0] == '/')
			return (ft_printf("no such file or directory: "),
				print_nonprintable(expa), free_tab(full_cmd), free(expa));
		return (ft_printf("command not found: "),
			print_nonprintable(expa), free_tab(full_cmd), free(expa));
	}
	cmd_args = get_cmd_and_args(full_cmd, 0);
	if (cmd_args == NULL)
		return (free_tab(full_cmd), free(cmd), free(expa));
	return (exec_cmds(cmd, cmd_args, mini),
		free_tab(full_cmd), free(cmd), free(expa), free_tab(cmd_args));
}

int	main(int argc, char **argv, char **envp)
{
	int		exit;
	char	*line;
	t_mini	*mini;

	if (argv[1])
		return (argc - argc + 1);
	signal(SIGQUIT, SIG_IGN);
	mini = init_mini(envp);
	if (!mini)
		return (perror("Error:"), 1);
	while (1)
	{
		g_signal = 0;
		line = readline("minishell> ");
		if (line == NULL)
			return (exit = ft_atoi(get_var_value(mini -> env_vars, "?")),
				printf("exit\n"), rl_clear_history(), free_mini(mini), exit);
		if (*line && !is_all_space(line))
		{
			add_history(line);
			if (!is_correctly_quoted(line))
				printf("Not correctly quoted\n");
			else
				parse_line(line, mini);
		}
		free(line);
		if (mini -> exit_status != -1)
			return (rl_clear_history(), free_mini(mini), mini -> exit_status);
	}
	if (g_signal != 0)
		return (exit = ft_atoi(get_var_value(mini -> env_vars, "?")),
			rl_clear_history(), free_mini(mini), exit);
	return (rl_clear_history(), free_mini(mini), 130);
}
