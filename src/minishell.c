/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:07:38 by vluo              #+#    #+#             */
/*   Updated: 2025/03/28 17:23:04 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <signal.h>

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

void	exec_cmd(char *path_cmd, t_env_vars *vars)
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
		ft_printf("to be implemented: %s\n", cmd);
	update_exit_status(vars, ft_strdup("0"));
	free_tab(paths);
}

void	test_sig(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return ;
	if (pid > 0)
	{
		kill(pid, SIGUSR1);
		waitpid(pid, 0, 0);
	}
	else
	{
		ft_printf("START WAIT\n");
		while (1)
			usleep(1);
		ft_printf("FINISHED WAIT\n");
		return ;
	}
}

void	parse_line(char *line, t_env_vars *vars)
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
	return (exec_cmd(cmd, vars), free_tab(full_cmd), free(cmd), free(expa));
}

int	main(int argc, char **argv, char **envp)
{
	char				*line;
	t_env_vars			*vars;
	int					i;
	int					correct;
	struct sigaction	**sas;

	vars = init_env_vars(envp);
	sas = init_sas();
	i = 0;
	while (i < 8)
	{
		ft_printf("signa : %d\n", g_signal);
		if (g_signal == 0)
		{
			write(2, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		g_signal = 0;
		ft_printf("START\n");
		line = readline("minishell> ");
		ft_printf("what you said : |%s|\n", line);
		if (line)
		{
			if (*line)
			{
				correct = is_correctly_quoted(line);
				while (correct != 0)
				{
					line = ft_strjoin_free(line, ft_strdup("\n"));
					if (correct == 1)
						line = ft_strjoin_free(line, readline("quote> "));
					else
						line = ft_strjoin_free(line, readline("dquote> "));
					correct = is_correctly_quoted(line);
				}
				add_history(line);
				parse_line(line, vars);
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
