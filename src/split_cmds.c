/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:42:54 by vluo              #+#    #+#             */
/*   Updated: 2025/04/21 14:48:49 by vluo             ###   ########.fr       */
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

/* split_expand manuel

	renvoie un tableau dont les elements sont les elements de split_cmds
	dont on a expanded
	split_expand[i] = expand(split_cmds[i])

Arguments : 
	- vars : dictionnaire contenant les variables d'environnemt

	- line : la ligne de commande a split 

	- splited_cmds : la ligne deja splite selon les mots 
	-> on utilise split_cmds pour recup cet argument (voir split_cmds manuel)

Valeurs de retour :
	- NULL : si erreur de malloc

	- un char ** avec pour elements chaque elements de splited_cmds expanded
	ex : pour line = "$PWD" hello '$existepas' "$existepas"
		 pour split_cmds = ["$PWD", hello, '$existepas', "$existepas"]
	-> split_expand(split_cmds, line, vars)
	renvoie => [/usr/Documents/..., hello, $existepas, ""]

	free le tableau avec free_tab
*/
char	**split_expand(char	**splited_cmds, char *line, t_env_vars *vars)
{
	char	**split_expanded;
	int		i;

	split_expanded = malloc(sizeof(char *) * (split_cmds_len(line) + 1));
	if (split_expanded == 0)
		return (0);
	split_expanded[split_cmds_len(line)] = 0;
	i = -1;
	while (splited_cmds[++i])
	{
		split_expanded[i] = expand(splited_cmds[i], vars);
		if (!split_expanded[i])
		{
			while (i >= 0)
				free(split_expanded[i]);
			free(split_expanded);
			return (NULL);
		}
		if (!ft_strncmp(splited_cmds[i], "<<", 3))
			i ++;
	}
	return (split_expanded);
}

char	**get_cmd_and_args(char *cmd, char **split, int index)
{
	int		i;
	int		j;
	char	**cmd_and_args;

	i = index - 1;
	while (split[++i] != 0)
		if (split[i][0] == '|')
			break ;
	cmd_and_args = ft_calloc((i - index) + 1, sizeof(char *));
	if (cmd_and_args == 0)
		return (NULL);
	cmd_and_args[i - index] = 0;
	cmd_and_args[0] = ft_strdup(cmd);
	j = 0;
	while (++j < i - index)
	{
		cmd_and_args[j] = ft_strdup(split[index + j]);
		if (cmd_and_args[j] == 0)
		{
			while (--j > 0)
				free(cmd_and_args[j]);
			free(cmd_and_args);
		}
	}
	return (cmd_and_args);
}
