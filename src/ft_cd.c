/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:44:33 by vluo              #+#    #+#             */
/*   Updated: 2025/05/14 11:05:40 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*gcwd(void)
{
	char	*buf;
	int		size;

	buf = NULL;
	size = 0;
	while (buf == NULL)
	{
		free(buf);
		buf = getcwd(NULL, ++size);
	}
	return (buf);
}

static char	*join_path(char *path, char *allpath)
{
	char	*path_sl;
	char	*correct_path;

	path_sl = ft_strjoin(allpath, "/");
	if (path_sl == 0)
		return (NULL);
	correct_path = ft_strjoin(path_sl, path);
	if (correct_path == 0)
		return (free(path_sl), NULL);
	return (free(path_sl), correct_path);
}

static char	*get_correct_path(char *path, t_env_vars *vars)
{
	char	*cdpath;
	char	**allpath;
	char	*correct_path;
	int		exit;
	int		i;

	cdpath = get_var_value(vars, "CDPATH");
	if (cdpath == 0 || path[0] == '/')
		return (ft_strdup(path));
	allpath = ft_split(cdpath, ':');
	i = -1;
	exit = 0;
	while (allpath[++i])
	{
		correct_path = join_path(path, allpath[i]);
		exit = chdir(correct_path);
		if (!exit)
			return (free_tab(allpath),
				printf("%s\n", correct_path), correct_path);
		free(correct_path);
	}
	return (free_tab(allpath), ft_strdup(path));
}

static char	*parse_path(char *path, t_env_vars *vars)
{
	char	*res;
	char	*corr_path;

	if (ft_strncmp(path, "~", 2) == 0 || ft_strncmp(path, "~/", 2) == 0)
		corr_path = ft_strdup(get_var_value(vars, "HOME"));
	else if (ft_strncmp(path, "-", 2) == 0)
	{
		corr_path = ft_strdup(get_var_value(vars, "OLDPWD"));
		if (corr_path)
			printf("%s\n", corr_path);
	}
	else
		corr_path = get_correct_path(path, vars);
	if (!corr_path)
		return (NULL);
	res = get_correct_path(corr_path, vars);
	free(corr_path);
	if (!res)
		return (NULL);
	return (res);
}

void	ft_cd(char *path, t_env_vars *vars)
{
	int		exit;
	char	*correct_path;
	char	*vl;

	if (path == 0)
	{
		correct_path = get_var_value(vars, "HOME");
		if (correct_path == 0)
		{
			vars_add(vars, "?", "0");
			return ;
		}
		exit = chdir(correct_path);
	}
	else
	{
		correct_path = parse_path(path, vars);
		exit = chdir(correct_path);
		free(correct_path);
	}
	if (exit)
		return (vl = ft_itoa(-exit), perror("cd"),
			vars_add(vars, "?", vl), free(vl));
	return (vars_add(vars, "OLDPWD", get_var_value(vars, "PWD")), vl = gcwd(),
		vars_add(vars, "PWD", vl), vars_add(vars, "?", "0"), free(vl));
}
