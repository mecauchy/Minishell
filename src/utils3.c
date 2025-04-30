/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:45:20 by vluo              #+#    #+#             */
/*   Updated: 2025/04/30 19:16:12 by vluo             ###   ########.fr       */
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

int	is_correct_deli(char *deli)
{
	if (!ft_strncmp("|>>", deli, 4))
		return (1);
	if (!ft_strncmp("|<<", deli, 4))
		return (1);
	if (ft_strlen(deli) >= 3)
		return (0);
	if (ft_strncmp("|>", deli, 3))
		return (1);
	if (ft_strncmp("|<", deli, 3))
		return (1);
	if (ft_strncmp("<", deli, 2))
		return (1);
	if (ft_strncmp(">", deli, 2))
		return (1);
	if (ft_strncmp("|", deli, 2))
		return (1);
	return (0);
}

int	is_correct_cmds(char *line)
{
	int		i;
	int		st_deli;
	char	*deli;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] != '\t'))
		i ++;
	if (line[i] && line[i] == '|')
		return (printf("bash: syntax error\n"), 0);
	while (line[i])
	{
		while (line[i] && (line[i] != ' ' && line[i] != '\t' && line[i] != '>'
			&& line[i] != '<' && line[i] != '|'))
			i ++;
		if (line[i])
			return (1);
		st_deli = i;
		while (line[i] && (line[i] == '>' || line[i] != '<' || line[i] != '|'))
			i ++;
		deli = ft_substr(line, st_deli, i - st_deli);
		if (!is_correct_deli(deli))
			return (free(deli), printf("bash: syntax error\n"), 0);
		free(deli);
		while (line[i] && (line[i] == '>' || line[i] != '<' || line[i] != '|'))
			i ++;
	}
	return (1);
}
