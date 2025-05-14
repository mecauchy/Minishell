/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_correct_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:10:02 by vluo              #+#    #+#             */
/*   Updated: 2025/05/14 17:21:00 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	skip_quote(char *line, int i)
{
	char	c;

	while (line[i] && (line[i] != '>' && line[i] != '<' && line[i] != '|'
			&& line[i] != '"' && line[i] != '\''))
		i ++;
	if (line[i] == '\'' || line[i] == '"')
	{
		c = line[i];
		while (line[++i])
			if (line[i] == c)
				return (i + 1);
	}
	return (i);
}

static int	correct_redir(char *line)
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
	return (i);
}

int	is_correct_cmds(char *line)
{
	int		i;
	int		st;

	i = -1;
	while (line[++i])
	{
		st = i;
		i = skip_quote(line, i);
		if (!line[i])
			return (!is_all_space(&line[st]));
		if (line[i] == '>' || line[i] == '<')
		{
			if (correct_redir(&line[i]) == -1)
				return (0);
			i += correct_redir(&line[i]);
		}
		if (!line[i])
			return (1);
		if (line[i] == '|')
			if (!line[i + 1] || i == 0)
				return (0);
	}
	return (1);
}
