/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:12:31 by vluo              #+#    #+#             */
/*   Updated: 2025/03/27 13:58:19 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	if (tmp -> name == NULL)
	{
		tmp -> name = name;
		tmp -> value = value;
		tmp -> next = NULL;
		return ;
	}
	while (tmp -> next != 0)
	{
		if (ft_strncmp(tmp -> name, name, ft_strlen(name)) == 0)
		{
			free(tmp -> value);
			free(name);
			tmp -> value = value;
			return ;
		}
		tmp = tmp -> next;
	}
	tmp -> next = init_var(name, value);
}

static int	add_spec_var(t_env_vars *vars)
{
	char	*name;
	char	*value;

	name = ft_strdup("?");
	value = ft_strdup("0");
	if (!name || !value)
		return (free(name), free(value), free_vars(vars), 1);
	return (vars_add_one(vars, name, value), 0);
}

t_env_vars	*init_env_vars(char **envp)
{
	t_env_vars	*vars;
	int			i;
	int			j;
	char		*name;
	char		*value;

	vars = malloc(sizeof(t_env_vars));
	if (vars == 0)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j ++;
		name = ft_substr(envp[i], 0, j);
		value = ft_strdup(getenv(name));
		if (!name || !value)
			return (free(name), free(value), free_vars(vars), NULL);
		vars_add_one(vars, name, value);
	}
	if (add_spec_var(vars))
		return (0);
	return (vars);
}

void	update_exit_status(t_env_vars *vars, char *status)
{
	t_env_vars	*tmp;

	tmp = vars;
	while (tmp -> next != 0)
		tmp = tmp -> next;
	free(tmp -> value);
	tmp -> value = status;
}
