/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:06:45 by vluo              #+#    #+#             */
/*   Updated: 2025/05/14 12:51:23 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_squote(char *line)
{
	int		i;

	i = 0;
	while (line[++i])
		if (line[i] == '\'')
			break ;
	if (!line[i])
		return (ft_strdup(line));
	return (ft_substr(line, 1, i - 1));
}

static char	*get_dquote(char *line, t_env_vars *vars)
{
	int		i;
	int		start;
	char	*joined;

	i = 1;
	joined = NULL;
	while (line[i])
	{
		start = i;
		while (line[i] && (line[i] != '"' && line[i] != '$'))
			i ++;
		joined = ft_strjoin_free(joined, ft_substr(line, start, i - start));
		if (!line[i] || line[i] == '"')
			return (joined);
		joined = ft_strjoin_free(joined, get_env_var(&line[i], vars));
		if (line[i + 1] && line[i + 1] == '?')
		{
			i += 2;
			continue ;
		}
		while (line[i] && line[i] != ' ' && line[i] != '\t'
			&& line[i] != '"' && line[i] != '\'')
			i ++;
	}
	return (joined);
}

/* Get_quote manuel

	renvoie line sans "" ou ''
	
	Precision pour le shell :
	- avec les "" on expand
		-> ex : get_quote("$l", vars) renvoie => valeur (si l = valeur)
	- avec les '' on ne expand PAS
		-> ex : get_quote('$l', vars) renvoie => $l
	
Arguments :
	- vars : est le dictionnaire dont on a stockees toutes 
	les variables d'enrinnement
	
	- line -> est la chaine de char dont on veut enlever les "" et les ''
	(il faut que line commence par un "" ou '')

Valeurs de retour :
	- la chaine de char sans les "" ou les ''
	- une copie de line si "" ou '' ne commance pas la chaine de char

*/
char	*get_quote(char *line, t_env_vars *vars)
{
	char	c;

	c = line[0];
	if (c == '\'')
		return (get_squote(line));
	if (c == '"')
		return (get_dquote(line, vars));
	return (ft_strdup(line));
}

char	*unquote(char *line)
{
	int		i;
	char	to_add[2];
	char	*unquoted;

	i = -1;
	to_add[1] = 0;
	unquoted = ft_strdup("");
	while (line[++i])
	{
		if (line[i] == '"' || line[i] == '\'')
			continue ;
		to_add[0] = line[i];
		unquoted = ft_strjoin_free(unquoted, ft_strdup(to_add));
	}
	return (unquoted);
}
