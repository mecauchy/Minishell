/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:19:06 by vluo              #+#    #+#             */
/*   Updated: 2025/03/25 17:45:01 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_name_var(char *line)
{
	int	i;

	i = 0;
	while (line[++i])
	{
		if (line[i] == '\'' || line[i] == '"')
			break ;
	}
	if (!line[i])
		if (line[i - 1] == '"')
			return (ft_substr(line, 1, i - 2));
	return (ft_substr(line, 1, i - 1));
}

/* Get_env_var manuel

Arguments :
	- envp : est la liste des variables d'environnement qu'on
	lance avec le programme
	on les recupes avec le main => int main(int argc, char **argv, char **envp)
	a passer a la fonction pour recupere les bonnes variables

	- line : est le nom de la variable d'environnement
			 dont on veut recuperer la valeur
	ex : $PWD / $hello / hello$world / hello

Valeur de retour : 
	- une copie (ft_strdup) de line si line ne comporte aucun $
	- si pour $var
		-> var existe alors renvoie -> un (char *) avec la bonne valeur
	-	-> var n'existe pas alors renvoie -> "" (une chaine vide) (pas NULL)
	ex : pour hello$w , si w existe alors renvoie -> helloworld (si w = world)
	ex : pour hello$w, si w n'existe pas alors renvoie -> hello

get_env_var renvoie tjs une chaine de char a free

(Cette fonction est presque juste une fonction statique utile pour expand
Pour evaluer une expression, utilise simplement expand)
*/
char	*get_env_var(char *line, char **envp)
{
	int		i;
	char	*var_name;
	char	*res;

	if (!line)
		return (NULL);
	var_name = get_name_var(line);
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(var_name, envp[i], ft_strlen(var_name)) == 0)
		{
			res = ft_substr(envp[i], ft_strlen(var_name) + 1,
					ft_strlen(envp[i]) - ft_strlen(var_name));
			return (free(var_name), res);
		}
	}
	return (free(var_name), ft_strdup(""));
}
