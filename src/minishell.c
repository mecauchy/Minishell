/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:07:38 by vluo              #+#    #+#             */
/*   Updated: 2025/04/29 13:54:24 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal;

void	exec_cmd(char *cmd, char **cmd_args, t_env_vars *vars)
{
	int		pid;
	char	**env;

	pid = fork();
	if (pid < 0)
		return (perror("Error: "));
	if (pid > 0)
		wait_upex(pid, vars);
	else
		return (env = get_envp(vars), vars_add(vars, "_", cmd), execve(cmd,
				cmd_args, env), printf("%s: command not found\n", cmd),
			free_tab(env), exit(127));
}

void	exec_cmds(char *path_cmd, char **cmd_args, t_mini *mini)
{
	char	**paths;
	char	*cmd;
	char	*_value;
	int		i;

	paths = ft_split(path_cmd, '/');
	if (paths == 0)
		return ;
	i = 0;
	while (paths[i])
		i ++;
	cmd = paths[i - 1];
	_value = get_last_arg(cmd_args, mini -> env_vars);
	if (!is_builtin(cmd, cmd_args, mini))
		exec_cmd(path_cmd, cmd_args, mini -> env_vars);
	vars_add(mini -> env_vars, "_", _value);
	free(_value);
	free_tab(paths);
}

void	parse_line(char *line, t_mini *mini)
{
	char	**full_cmd;
	char	*expa;
	char	*cmd;
	char	**cmd_args;

	if (ft_strchr(line, '<'))
	{
		g_signal = SIGUSR1;
		return (here_doc_cmd(line, mini));
	}
	full_cmd = split_cmds(line);
	expa = expand(full_cmd[0], mini -> env_vars);
	if (expa == NULL || !expa[0])
		return (free_tab(full_cmd), free(expa));
	cmd = get_correct_cmd(expa);
	if (cmd == NULL)
		cmd = ft_strdup(expa);
	cmd_args = get_cmd_and_args(cmd, full_cmd, 0);
	if (cmd_args == NULL)
		return (free_tab(full_cmd), free(cmd), free(expa), free_tab(cmd_args));
	return (exec_cmds(cmd, cmd_args, mini),
		free_tab(full_cmd), free(cmd), free(expa), free_tab(cmd_args));
}

void	handle_line(t_mini *mini, char *line)
{
	int	ex;

	if (g_signal == SIGUSR2)
	{
		g_signal = 0;
		vars_add(mini -> env_vars, "?", "130");
	}
	if (line == NULL)
		return (ex = ft_atoi(get_var_value(mini -> env_vars, "?")),
			printf("exit\n"), rl_clear_history(), free_mini(mini), exit(ex));
	if (*line && !is_all_space(line))
	{
		add_history(line);
		if (!is_correctly_quoted(line))
		{
			printf("Not correctly quoted\n");
			vars_add(mini -> env_vars, "?", "2");
		}
		else
			parse_line(line, mini);
	}
	free(line);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_mini	*mini;
	int		exit;

	if (argv[1])
		return (argc - argc + 1);
	signal(SIGQUIT, SIG_IGN);
	mini = init_mini(envp);
	if (!mini)
		return (perror("Error"), 1);
	while (1)
	{
		g_signal = 0;
		line = readline("minishell> ");
		handle_line(mini, line);
		if (mini -> do_exit)
			return (rl_clear_history(), exit = mini -> exit_status,
				free_mini(mini), exit);
	}
	return (0);
}
