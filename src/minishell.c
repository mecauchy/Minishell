/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:07:38 by vluo              #+#    #+#             */
/*   Updated: 2025/03/27 13:53:33 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	parse_line(char *line, t_env_vars *vars)
{
	char	**full_cmd;
	char	*expa;
	char	*cmd;

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
	char		*line;
	t_env_vars	*vars;
	int			i;
	int			correct;

	vars = init_env_vars(envp);
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
	argv ++;
	envp ++;
	return (argc - argc);
}
