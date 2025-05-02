/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:38:13 by vluo              #+#    #+#             */
/*   Updated: 2025/05/02 16:51:26 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_array	*init_array(void)
{
	t_array	*tab;

	tab = ft_calloc(1, sizeof(t_array));
	if (tab == 0)
		return (NULL);
	tab -> tot_len = 2;
	tab -> arr_i = 0;
	tab -> arr = ft_calloc(3, sizeof(char *));
	if (tab -> arr == 0)
		return (free(tab), NULL);
	return (tab);
}

static t_cmd	*init_cmds(int nb_cmd)
{
	t_cmd	*cmds;
	int		i;

	cmds = ft_calloc(1, sizeof(t_cmd));
	if (cmds == 0)
		return (NULL);
	cmds->args = ft_calloc((nb_cmd + 1), sizeof(t_array *));
	cmds->redir = ft_calloc((nb_cmd + 1), sizeof(t_redir *));
	if (!cmds->args || !cmds->redir)
		return (free(cmds->args), free(cmds->redir), free(cmds), NULL);
	i = -1;
	while (++i < nb_cmd)
	{
		cmds->args[i] = init_array();
		cmds->redir[i] = ft_calloc(1, sizeof(t_redir));
		if (!cmds->args[i] || !cmds->redir[i])
			return (free_cmds(cmds), NULL);
	}
	return (cmds);
}

static void	parse_add(t_cmd *cmds, char **av, int *i, int *nb_cmd)
{
	if (av[*i][0] == '<' || av[*i][0] == '>')
	{
		cmds->redir[*nb_cmd]->type = ft_strdup(av[*i]);
		cmds->redir[*nb_cmd]->file = ft_strdup(av[*i + 1]);
		if (!cmds->redir[*nb_cmd] || !cmds->redir[*nb_cmd])
			return (free_cmds(cmds));
		*i += 2;
	}
	if (!av[*i])
		return ;
	if (av[*i][0] == '|')
	{
		*nb_cmd += 1;
		*i += 1;
	}
	if (av[*i] && av[*i][0] != '>' && av[*i][0] != '<')
	{
		cmds->args[*nb_cmd]->arr = append(cmds->args[*nb_cmd]->arr,
				&cmds->args[*nb_cmd]->tot_len,
				&cmds->args[*nb_cmd]->arr_i, ft_strdup(av[*i]));
		if (cmds->args[*nb_cmd]->arr == 0)
			return (free_cmds(cmds));
		*i += 1;
	}
}

static void	parse_cmds(t_cmd *cmds, char **av)
{
	int		i;
	int		nb_cmd;

	i = 0;
	nb_cmd = 0;
	while (av[i])
	{
		parse_add(cmds, av, &i, &nb_cmd);
		if (cmds == 0)
			return ;
	}
}

t_cmd	*get_cmds(char **av)
{
	int		nb_cmds;
	t_cmd	*cmds;

	nb_cmds = nb_cmd(av);
	cmds = init_cmds(nb_cmds);
	if (!cmds)
		return (NULL);
	parse_cmds(cmds, av);
	if (!cmds)
		return (NULL);
	return (cmds);
}
