/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:30:14 by vluo              #+#    #+#             */
/*   Updated: 2025/05/06 22:27:46 by vluo             ###   ########.fr       */
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
