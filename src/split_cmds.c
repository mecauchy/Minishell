/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:42:54 by vluo              #+#    #+#             */
/*   Updated: 2025/05/07 00:42:39 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	end_word(char *line, char ***sp, int *len_tot, int *sp_i)
{
	int		i;
	char	c;
	char	*sub;

	i = 0;
	while (line[i] && (line[i] != ' ' && line[i] != '\t' && line[i] != '>'
			&& line[i] != '<' && line[i] != '|'))
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			c = line[i++];
			while (line[i] && line[i] != c)
				i ++;
		}
		i ++;
	}
	sub = ft_substr(line, 0, i);
	if (sub == 0)
		return (free_tab(*sp), -1);
	if (!sub[0])
		return (free(sub), i);
	*sp = append(*sp, len_tot, sp_i, sub);
	if (sp == 0)
		return (-1);
	return (i);
}

static int	end_deli(char *line, char ***sp, int *len_tot, int *sp_i)
{
	int		i;
	int		st_deli;
	char	*sub;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i ++;
	if (!line[i])
		return (i);
	st_deli = i;
	while (line[i] && (line[i] == '>' || line[i] == '<' || line[i] == '|'))
		i ++;
	sub = ft_substr(line, st_deli, i - st_deli);
	if (sub == 0)
		return (free_tab(*sp), -1);
	if (!is_all_space(sub))
		*sp = append(*sp, len_tot, sp_i, sub);
	else
		free(sub);
	if (*sp == 0)
		return (-1);
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i ++;
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
	char	**sp;
	int		len_tot;
	int		i;
	int		sp_i;

	i = 0;
	sp_i = 0;
	len_tot = 2;
	sp = ft_calloc(3, sizeof(char *));
	if (sp == 0)
		return (NULL);
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i ++;
	while (line[i])
	{
		i += end_word(&line[i], &sp, &len_tot, &sp_i);
		if (sp == 0)
			return (0);
		i += end_deli(&line[i], &sp, &len_tot, &sp_i);
		if (sp == 0)
			return (0);
	}
	return (sp);
}

static void	add_expanded(char **splited_cmds, char **split_expanded,
		t_env_vars *vars, int *i)
{
	if (!ft_strncmp(splited_cmds[*i], "<<", 3))
	{
		split_expanded[*i] = ft_strdup(splited_cmds[*i]);
		*i += 1;
		split_expanded[*i] = ft_strdup(splited_cmds[*i]);
		if (!split_expanded[*i] || !split_expanded[*i - 1])
		{
			free(split_expanded[*i]);
			free(split_expanded[*i - 1]);
			free_tab(split_expanded);
			return ;
		}
		return ;
	}
	split_expanded[*i] = expand(splited_cmds[*i], vars);
	if (!split_expanded[*i])
	{
		while (*i >= 0)
			free(split_expanded[*i]);
		return (free(split_expanded));
	}
	return ;
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
char	**split_expand(char	**splited_cmds, t_env_vars *vars)
{
	char	**split_expanded;
	int		i;

	i = 0;
	while (splited_cmds[i])
		i ++;
	split_expanded = ft_calloc(i + 1, (sizeof(char *)));
	if (split_expanded == 0)
		return (0);
	i = -1;
	while (splited_cmds[++i])
	{
		add_expanded(splited_cmds, split_expanded, vars, &i);
		if (split_expanded == 0)
			return (NULL);
	}
	return (split_expanded);
}
