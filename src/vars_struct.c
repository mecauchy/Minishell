/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:12:31 by vluo              #+#    #+#             */
/*   Updated: 2025/03/31 11:46:31 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	vars_add_one(t_env_vars *vars, char *name, char *value)
{
	t_env_vars	*tmp;

	tmp = vars;
	if (tmp -> name == NULL)
	{
		tmp -> name = name;
		tmp -> value = value;
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
	tmp -> next = ft_calloc(1, sizeof(t_env_vars));
	if (tmp -> next == 0)
		return ;
	tmp -> next -> name = name;
	tmp -> next -> value = value;
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
		value = ft_strdup(getenv(name));
		if (!name || !value)
			return (free(name), free(value), free_vars(vars), NULL);
		vars_add_one(vars, name, value);
	}
	if (add_spec_var(vars))
		return (0);
	return (vars);
}

void	del_one_var(t_env_vars *vars, char *name)
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
		}
		tmp = tmp -> next;
	}
}
