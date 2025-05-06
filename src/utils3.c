/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:45:20 by vluo              #+#    #+#             */
/*   Updated: 2025/05/06 22:58:17 by vluo             ###   ########.fr       */
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

int	nb_cmd(char **av)
{
	int	i;
	int	nb_cmd;

	nb_cmd = 0;
	i = -1;
	while (av[++i])
	{
		if (av[i][0] == '|')
			nb_cmd ++;
	}
	return (nb_cmd + 1);
}

void	free_cmds(t_cmd *cmds)
{
	int	i;
	int	nb_redir;

	if (!cmds)
		return ;
	i = -1;
	while (cmds->args[++i])
	{
		if (cmds->args[i]->arr)
			free_tab(cmds->args[i]->arr);
		free(cmds->args[i]);
	}
	i = -1;
	while (cmds->redir[++i])
	{
		nb_redir = -1;
		while (cmds->redir[i][++nb_redir])
		{
			free(cmds->redir[i][nb_redir]->type);
			free(cmds->redir[i][nb_redir]->file);
			free(cmds->redir[i][nb_redir]);
		}
		free(cmds->redir[i]);
	}
	return (free(cmds->args), free(cmds->redir), free(cmds));
}

char	**append(char **sp, int *len_tot, int *sp_i, char *sub)
{
	int		i;
	char	**split_double;

	if (sub == 0)
		return (free_tab(sp), NULL);
	if (*sp_i < *len_tot)
	{
		*sp_i += 1;
		return (sp[*sp_i - 1] = sub, sp);
	}
	split_double = ft_calloc((*len_tot * 2) + 1, sizeof(char *));
	if (!split_double)
		return (free_tab(sp), NULL);
	i = -1;
	while (sp[++i])
		split_double[i] = sp[i];
	return (split_double[i] = sub, split_double[i + 1] = 0,
		*len_tot = *len_tot * 2, *sp_i = i + 1, free(sp), split_double);
}

int	correct_redir(char *line)
{
	int		i;
	int		st;
	char	*sub;

	i = 1;
	if (!line[i])
		return (-1);
	if (line[0] == line[1])
		i ++;
	st = i;
	while (line[i] && line[i] != '<' && line[i] != '>' && line[i] != '|')
		i ++;
	if (!line[i])
	{
		if (st == i || is_all_space(&line[st]))
			return (-1);
		return (i);
	}
	sub = ft_substr(line, st, i - st);
	if (is_all_space(sub))
		return (free(sub), -1);
	free(sub);
	if (line[i] == '<' || line[i] == '>')
		return (correct_redir(&line[i]));
	return (i + 1);
}

int	is_correct_cmds(char *line)
{
	int		i;
	int		st;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i ++;
	while (line[i])
	{
		st = i;
		while (line[i] && (line[i] != '>' && line[i] != '<' && line[i] != '|'))
			i ++;
		if (!line[i])
			return (!is_all_space(&line[st]));
		if (line[i] == '>' || line[i] == '<')
		{
			if (correct_redir(&line[i]) == -1)
				return (0);
			i += correct_redir(&line[i]);
		}
		if (line[i] == '|')
			if (st == i)
				return (0);
		i ++;
	}
	return (1);
}
