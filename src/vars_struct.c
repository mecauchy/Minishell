/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:12:31 by vluo              #+#    #+#             */
/*   Updated: 2025/04/21 14:33:27 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_env_vars	*init_var(t_env_vars *vars, char *name, char *value)
{
	t_env_vars	*var;

	if (vars == 0)
	{
		var = ft_calloc(1, sizeof(t_env_vars));
		if (var == 0)
			return (NULL);
		var -> name = ft_strdup(name);
		var -> value = ft_strdup(value);
		return (var);
	}
	vars -> name = ft_strdup(name);
	vars -> value = ft_strdup(value);
	if (!vars -> name || !vars -> value)
		return (free(vars -> name), free(vars -> value), NULL);
	return (vars);
}

int	vars_add(t_env_vars *vars, char *name, char *value)
{
	t_env_vars	*tmp;

	tmp = vars;
	if (tmp -> name == NULL)
	{
		tmp = init_var(vars, name, value);
		if (!tmp)
			return (0);
		return (1);
	}
	while (tmp -> next != 0
		&& ft_strncmp(tmp -> name, name, ft_strlen(tmp -> name)))
		tmp = tmp -> next;
	if (ft_strncmp(tmp -> name, name, ft_strlen(tmp -> name)) != 0)
	{
		tmp -> next = init_var(NULL, name, value);
		if (tmp -> next == 0)
			return (free_vars(vars), 0);
		return (1);
	}
	free(tmp -> value);
	tmp -> value = ft_strdup(value);
	if (!tmp -> value)
		return (free(tmp -> name), free_vars(vars), 0);
	return (1);
}

t_env_vars	*init_env_vars(char **envp)
{
	t_env_vars	*vars;
	int			i;
	int			j;
	char		*name;

	vars = ft_calloc(1, sizeof(t_env_vars));
	if (vars == 0)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j ++;
		name = ft_substr(envp[i], 0, j);
		if (!name)
			return (free(name), free_vars(vars), NULL);
		if (!vars_add(vars, name, getenv(name)))
			return (free(name), free_vars(vars), NULL);
		free(name);
	}
	if (!vars_add(vars, "?", "0"))
		return (free_vars(vars), NULL);
	return (vars);
}

void	vars_del_one(t_env_vars *vars, char *name)
{
	t_env_vars	*tmp;
	t_env_vars	*del;

	tmp = vars;
	if (tmp == 0)
		return ;
	while (tmp -> next != 0)
	{
		if (ft_strncmp(tmp -> next -> name, name, ft_strlen(name)) == 0)
		{
			del = tmp -> next;
			tmp -> next = tmp -> next -> next;
			free(del -> name);
			free(del -> value);
			free(del);
			return ;
		}
		tmp = tmp -> next;
	}
}
