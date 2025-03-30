/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:07:38 by vluo              #+#    #+#             */
/*   Updated: 2025/03/30 19:16:29 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal;

void	print_path(void)
{
	ft_printf("getenv : %s\n", getenv("PWD"));
}

void	print_env(t_env_vars *vars)
{
	t_env_vars	*tmp;

	tmp = vars;
	while (tmp -> next != NULL)
	{
		ft_printf("%s=%s\n", tmp -> name, tmp -> value);
		tmp = tmp -> next;
	}
}

void	exec_cmd(char *cmd, char **envp)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (perror("Error: "));
	if (pid > 0)
	{
		kill(pid, SIGUSR1);
		waitpid(pid, 0, 0);
	}
	else
	{
		execve(cmd, ft_split(cmd, ' '), envp);
		return (perror("Error:"));
	}
}

void	exec_cmds(char *path_cmd, t_env_vars *vars, char **envp)
{
	char	**paths;
	char	*cmd;
	int		i;

	paths = ft_split(path_cmd, '/');
	i = 0;
	while (paths[i])
		i ++;
	cmd = paths[i - 1];
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		print_path();
	else if (ft_strncmp(cmd, "env", 4) == 0)
		print_env(vars);
	else
		exec_cmd(path_cmd, envp);
	update_exit_status(vars, ft_strdup("0"));
	free_tab(paths);
}

void test_sig(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (perror("Error:"));
	if (pid > 0)
	{
		kill(pid, SIGUSR1);
		waitpid(pid, 0, 0);
	}
	else if (pid == 0)
	{
		while(1)
			sleep(1);
		exit(0);
	}
	return ;
}

void	parse_line(char *line, t_env_vars *vars, char **envp)
{
	char	**full_cmd;
	char	*expa;
	char	*cmd;

	if (ft_strncmp(line, "test", 4) == 0)
		return (test_sig());
		
	full_cmd = split_cmds(line);
	expa = expand(full_cmd[0], vars);
	if (expa == NULL || !expa[0])
		return (free_tab(full_cmd), free(expa));
	ft_printf("expa : %s\n", expa);
	cmd = get_correct_cmd(expa);
	if (cmd == NULL)
	{
		update_exit_status(vars, ft_strdup("127"));
		if (expa[0] && expa[0] == '/')
			return (ft_printf("zsh: no such file or directory:"),
				print_nonprintable(expa), ft_printf("\n"),
				free_tab(full_cmd), free(expa));
		return (ft_printf("zsh: command not found: "),
			print_nonprintable(expa), ft_printf("\n"),
			free_tab(full_cmd), free(expa));
	}
	return (exec_cmds(cmd, vars, envp), free_tab(full_cmd), free(cmd), free(expa));
}

int	main(int argc, char **argv, char **envp)
{
	char				*line;
	t_env_vars			*vars;
	int					i;
	int					incorrect;
	struct sigaction	**sas;

	vars = init_env_vars(envp);
	sas = init_sas();
	g_signal = 0;
	i = 0;
	while (i < 8)
	{
		usleep(1000);
		g_signal = 0;
		line = readline("minishell> ");
		if (line)
		{
			if (*line)
			{
				add_history(line);
				incorrect = is_correctly_quoted(line);
				if (incorrect)
					printf("Not correctly quoted\n");
				else
					parse_line(line, vars, envp);
			}
			free(line);
		} 
		i ++;
	}
	rl_clear_history();
	free_vars(vars);
	free_sas(sas);
	argv ++;
	envp ++;
	return (argc - argc);
}
