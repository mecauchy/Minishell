/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:12:31 by vluo              #+#    #+#             */
/*   Updated: 2025/03/26 17:27:13 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_vars(t_env_vars *vars)
{
	if (vars != NULL)
	{
		free_vars(vars -> next);
		free(vars -> name);
		free(vars -> value);
		free(vars);
	}
}

t_env_vars	*init_var(char *name, char *value)
{
	t_env_vars	*var;

	var = malloc(sizeof(t_env_vars));
	if (var == 0)
		return (0);
	var -> name = name;
	var -> value = value;
	var -> next = 0;
	return (var);
}

void	vars_add_one(t_env_vars *vars, char *name, char *value)
{
	t_env_vars	*tmp;

	tmp = vars;
	while (tmp -> next != 0)
		tmp = tmp -> next;
	tmp -> next = init_var(name, value);
}

t_env_vars	*init_env_vars(char **envp)
{
	t_env_vars	*vars;
	int			i;
	int			j;
	char		*name;

	if (!envp[0])
		return (NULL);
	j = 0;
	while (envp[0][j] && envp[0][j] != '=')
		j ++;
	name = ft_substr(envp[0], 0, j);
	vars = init_var(name, ft_strdup(getenv(name)));
	if (!vars || !vars -> name || !vars -> value)
		return (free_vars(vars), NULL);
	i = 0;
	while (envp[++i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j ++;
		name = ft_substr(envp[i], 0, j);
		vars_add_one(vars, name, ft_strdup(getenv(name)));
	}
	return (vars);
}

char	*get_var_value(t_env_vars*vars, char *name)
{
	t_env_vars	*tmp;

	tmp = vars;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp -> name, name, ft_strlen(name)) == 0)
			return (tmp -> value);
		tmp = tmp -> next;
	}
	return (NULL);
}
