/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:07:38 by vluo              #+#    #+#             */
/*   Updated: 2025/03/25 16:26:04 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_path(void)
{
	ft_printf("getenv : %s\n", getenv("PWD"));
}

void	print_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		ft_printf("%s\n", env[i]);
}

void	exec_cmd(char *path_cmd, char **envp)
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
	if (ft_strncmp(cmd, "env", 4) == 0)
		print_env(envp);
	free_tab(paths);
}

void	parse_line(char *line, char **envp)
{
	char	**line_sp;
	char	*expa;
	char	*cmd;

	line_sp = split_cmds(line);
	expa = expand(line_sp[0], envp);
	if (expa == NULL || !expa[0])
		return (free_tab(line_sp), free(expa));
	ft_printf("expa : %s\n", expa);
	cmd = get_correct_cmd(expa);
	if (cmd == NULL)
	{
		if (expa[0] && expa[0] == '/')
			return (ft_printf("zsh : no such file or directory: %s\n",
					expa), free_tab(line_sp), free(expa));
		return (ft_printf("zsh : command not found: %s\n", expa)
			, free_tab(line_sp), free(expa));
	}
	return (exec_cmd(cmd, envp), free_tab(line_sp), free(cmd), free(expa));
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	int		i;

	i = 0;
	while (i < 8)
	{
		line = readline("minishell> ");
		if (line)
		{
			if (!(*line))
				rl_on_new_line();
			else
			{
				add_history(line);
				parse_line(line, envp);
			}
			free(line);
		}
		i ++;
	}
	rl_clear_history();
	argv ++;
	envp ++;
	return (argc - argc);
}
