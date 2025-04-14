/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_correct_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:42:21 by vluo              #+#    #+#             */
/*   Updated: 2025/04/14 12:26:12 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_correct_cmd_absol(char *cmd)
{
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

static char	*get_correct_cmd_rela(char *cmd)
{
	char	**cmd_no_arg;
	char	**paths;
	char	*path_cmd;
	char	*correct_path;
	int		i;

	cmd_no_arg = ft_split(cmd, ' ');
	paths = ft_split(getenv("PATH"), ':');
	i = -1;
	while (paths[++i])
	{
		path_cmd = ft_strjoin(paths[i], "/");
		correct_path = ft_strjoin(path_cmd, cmd_no_arg[0]);
		free(path_cmd);
		if (access(correct_path, F_OK | X_OK) == 0)
		{
			free_tab(cmd_no_arg);
			free_tab(paths);
			return (correct_path);
		}
		free(correct_path);
	}
	free_tab(cmd_no_arg);
	free_tab(paths);
	return (NULL);
}

char	*get_correct_cmd(char *cmd)
{
	if (!cmd)
		return (NULL);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (ft_strdup("export"));
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (ft_strdup("exit"));
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (ft_strdup("cd"));
	if (cmd && cmd[0] && (cmd[0] == '/' || cmd[0] == '.'))
		return (get_correct_cmd_absol(cmd));
	return (get_correct_cmd_rela(cmd));
}
