/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:45:20 by vluo              #+#    #+#             */
/*   Updated: 2025/05/05 20:44:51 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_all_space(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (!((8 <= line[i] && line[i] <= 13) || line[i] == 32))
			return (0);
	return (1);
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
