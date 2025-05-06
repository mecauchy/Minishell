/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:38:13 by vluo              #+#    #+#             */
/*   Updated: 2025/05/07 00:45:41 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_redir(t_cmd *cmd, int nb_cmd, int nb_redir)
{
	cmd->redir[nb_cmd] = ft_calloc(nb_redir + 1, sizeof(t_redir *));
	if (cmd->redir[nb_cmd] == 0)
		return (free_cmds(cmd));
	while (--nb_redir >= 0)
	{
		cmd->redir[nb_cmd][nb_redir] = ft_calloc(1, sizeof(t_redir));
		if (cmd->redir[nb_cmd][nb_redir] == 0)
		{
			while (cmd->redir[nb_cmd][++nb_redir] == 0)
				free(cmd->redir[nb_cmd][++nb_redir]);
			return (free(cmd->redir[nb_cmd]), free_cmds(cmd));
		}
	}
}

static	void	init_redirs(t_cmd *cmd, char **av)
{
	int		i;
	int		nb_redir;
	int		nb_cmd;

	nb_cmd = 0;
	nb_redir = 0;
	i = -1;
	while (av[++i])
	{
		if (ft_strncmp(av[i], "<<", 3) != 0
			&& (av[i][0] == '>' || av[i][0] == '<'))
			nb_redir ++;
		if (av[i][0] == '|')
		{
			init_redir(cmd, nb_cmd, nb_redir);
			nb_cmd ++;
			nb_redir = 0;
		}
	}
	init_redir(cmd, nb_cmd, nb_redir);
	return ;
}

static t_cmd	*init_cmds(int nb_cmd, char **av)
{
	t_cmd	*cmds;
	int		i;

	cmds = ft_calloc(1, sizeof(t_cmd));
	if (cmds == 0)
		return (NULL);
	cmds->args = ft_calloc((nb_cmd + 1), sizeof(t_array *));
	cmds->redir = ft_calloc((nb_cmd + 1), sizeof(t_redir **));
	if (!cmds->args || !cmds->redir)
		return (free(cmds->args), free(cmds->redir), free(cmds), NULL);
	init_redirs(cmds, av);
	i = -1;
	while (++i < nb_cmd)
	{
		cmds->args[i] = init_array();
		if (!cmds->args[i])
			return (free_cmds(cmds), NULL);
	}
	return (cmds);
}

static void	parse_add(t_cmd *cmds, char **av, int *i, int *nb_cmd)
{
	if (av[*i] && av[*i][0] == '|')
	{
		*nb_cmd += 1;
		*i += 1;
	}
	if (av[*i])
	{
		cmds->args[*nb_cmd]->arr = append(cmds->args[*nb_cmd]->arr,
				&cmds->args[*nb_cmd]->tot_len,
				&cmds->args[*nb_cmd]->arr_i, ft_strdup(av[*i]));
		if (cmds->args[*nb_cmd]->arr == 0)
			return (free_cmds(cmds));
		*i += 1;
	}
}

t_cmd	*get_cmds(char **av)
{
	int		i;
	int		r_i;
	int		cmd_i;
	t_cmd	*cmds;

	cmds = init_cmds(nb_cmd(av), av);
	i = 0;
	cmd_i = 0;
	r_i = 0;
	while (av[i] && cmds)
	{
		if (ft_strncmp(av[i], "<<", 3) != 0
			&& (av[i][0] == '<' || av[i][0] == '>'))
		{
			cmds->redir[cmd_i][r_i]->type = ft_strdup(av[i++]);
			cmds->redir[cmd_i][r_i++]->file = ft_strdup(av[i++]);
			if (!cmds->redir[cmd_i][r_i - 1] || !cmds->redir[cmd_i][r_i - 1])
				return (free_cmds(cmds), NULL);
		}
		if (av[i] && av[i][0] == '|')
			r_i = 0;
		parse_add(cmds, av, &i, &cmd_i);
	}
	return (cmds);
}
