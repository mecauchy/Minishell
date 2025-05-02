/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:30:14 by vluo              #+#    #+#             */
/*   Updated: 2025/05/02 16:40:47 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

	if (!cmds)
		return ;
	i = -1;
	while (cmds->args[++i] != 0)
	{
		if (cmds->args[i]->arr)
			free_tab(cmds->args[i]->arr);
		free(cmds->args[i]);
	}
	free(cmds->args);
	i = -1;
	while (cmds->redir[++i] != 0)
	{
		free(cmds->redir[i]->type);
		free(cmds->redir[i]->file);
		free(cmds->redir[i]);
	}
	free(cmds->redir);
	free(cmds);
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
