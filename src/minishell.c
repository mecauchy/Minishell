/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:07:38 by vluo              #+#    #+#             */
/*   Updated: 2025/03/26 17:47:48 by vluo             ###   ########.fr       */
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
	while (tmp != NULL)
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
		if (expa[0] && expa[0] == '/')
			return (ft_printf("zsh: no such file or directory: %s\n",
					expa), free_tab(full_cmd), free(expa));
		return (ft_printf("zsh: command not found: %s\n", expa)
			, free_tab(full_cmd), free(expa));
	}
	return (exec_cmd(cmd, vars), free_tab(full_cmd), free(cmd), free(expa));
}

int	is_correctly_quoted(char *line)
{
	int		i;
	char	c;
	
	i = -1;
	while (line[++i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			c = line[i++];
			while (line[i] && line[i] != c)
				i ++;
			if (!line[i])
			{
				if (c == '\'')
					return (1);
				else
					return (2);
			}
		}
	}
	return (0);
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
