/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:42:54 by vluo              #+#    #+#             */
/*   Updated: 2025/03/25 17:41:29 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	split_cmds_len(char *line)
{
	int		i;
	int		len;
	char	c;

	i = 0;
	len = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i ++;
	while (line[i])
	{
		while (line[i] && (line[i] != ' ' && line[i] != '\t'))
		{
			if (line[i] == '\'' || line[i] == '"')
			{
				c = line[i++];
				while (line[i] && line[i] != c)
					i ++;
			}
			i ++;
		}
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i ++;
		len ++;
	}
	return (len);
}

static int	go_to_end_word(char *line, int start, char **line_sp, int *cpt)
{
	int		i;
	char	c;

	i = start;
	while (line[i] && (line[i] != ' ' && line[i] != '\t'))
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			c = line[i++];
			while (line[i] && line[i] != c)
				i ++;
		}
		i ++;
	}
	line_sp[*cpt] = ft_substr(line, start, i - start);
	if (line_sp[*cpt] == 0)
	{
		i = *cpt;
		while (--i >= 0)
			free(line_sp[i]);
		free(line_sp);
		return (-1);
	}
	*cpt += 1;
	return (i);
}

/* split_cmds manuel

Arguments:
    - line : l'instruction donner au programme (recuperer par readline)
    ex: minishell> 'cat ' fichier

Valeur de retour :
    - NULL si il y a eu une erreur de malloc
    - un tableau de chaine de caracteres (char **) avec dernier element 0
    -> ex : pour line = "cat fichier1" fichier2 ...
        => split_cmds(line) renvoie -> ["cat fichier1", fichier2, ...]

split_cmds renvoie tjs quelque chose qu'il faut free apres utilisation
(-> utiliser free_tab pour free le char **)

*/
char	**split_cmds(char *line)
{
	char	**line_sp;
	int		i;
	int		cpt;

	line_sp = malloc(sizeof(char *) * (split_cmds_len(line) + 1));
	if (line_sp == NULL)
		return (NULL);
	line_sp[split_cmds_len(line)] = 0;
	i = 0;
	cpt = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i ++;
	while (line[i])
	{
		i = go_to_end_word(line, i, line_sp, &cpt);
		if (i == -1)
			return (NULL);
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i ++;
	}
	return (line_sp);
}
