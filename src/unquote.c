/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:06:45 by vluo              #+#    #+#             */
/*   Updated: 2025/03/25 18:37:23 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_squote(char *line)
{
	int		i;

	i = 1;
	while (line[i])
		if (line[i++] == '\'')
			break ;
	if (!line[i])
		return (ft_strdup(line));
	return (ft_substr(line, 1, i - 1));
}

static char	*get_dquote(char *line, char **envp)
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
		else
			joined = ft_strjoin_free(joined, get_env_var(&line[i], envp));
		while (line[i] && line[i] != '\'')
			i ++;
	}
	return (joined);
}

/* Get_quote manuel

	renvoie line sans "" ou ''
	
	Precision pour le shell :
	- avec les "" on expand
		-> ex : get_quote("$l", envp) renvoie => valeur (si l = valeur)
	- avec les '' on ne expand PAS
		-> ex : get_quote('$l', envp) renvoie => $l
	

Arguments :
	- envp : est les variables d'environnement qu'on lance avec le programme
	on les recupes avec le main => int main(int argc, char **argv, char **envp)
	a passer a la fonction pour recupere les bonnes variables
	
	- line -> est la chaine de char dont on veut enlever les "" et les ''
	(il faut que line commence par un "" ou '')

Valeurs de retour :
	- la chaine de char sans les "" ou les ''
	- une copie de line si "" ou '' ne commance pas la chaine de char

*/
char	*get_quote(char *line, char **envp)
{
	char	c;

	c = line[0];
	if (c == '\'')
		return (get_squote(line));
	if (c == '"')
		return (get_dquote(line, envp));
	return (ft_strdup(line));
}
