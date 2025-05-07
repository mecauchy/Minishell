/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:19:06 by vluo              #+#    #+#             */
/*   Updated: 2025/05/07 15:09:08 by vluo             ###   ########.fr       */
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

char	*get_var_value(t_env_vars *vars, char *name)
{
	t_env_vars	*tmp;

	tmp = vars;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp -> name, name, ft_strlen(name)) == 0)
			return (tmp -> value);
		tmp = tmp -> next;
	}
	return (NULL);
}

/* Get_env_var manuel

Arguments :
	- vars : est le dictionnaire dont on a stockees toutes 
	les variables d'enrinnement

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
char	*get_env_var(char *line, t_env_vars *vars)
{
	char	*var_name;
	char	*res;

	if (!line)
		return (NULL);
	var_name = get_name_var(line);
	if (!var_name || !var_name[0])
		return (free(var_name), ft_strdup(""));
	res = get_var_value(vars, var_name);
	if (res != NULL)
		return (free(var_name), ft_strdup(res));
	return (free(var_name), ft_strdup(""));
}

static	char	*join_name_value(t_env_vars *var)
{
	char	*join;
	char	*s1;
	char	*s2;

	s1 = ft_strdup(var -> name);
	s2 = ft_strdup("=");
	if (!s1 || !s2)
		return (free(s1), free(s2), NULL);
	s1 = ft_strjoin_free(s1, s2);
	s2 = ft_strdup(var -> value);
	if (!s1 || !s2)
		return (free(s1), free(s2), NULL);
	join = ft_strjoin_free(s1, s2);
	if (join == 0)
		return (0);
	return (join);
}

/* get_envp manuel

	=> obitent un tableau de env vars : ["var1=value1", "var2=val2", ..., 0]

Arguments : 
	- vars : dictionnaire contenant toutes les var d'env

Valeurs de retour : 
	- NULL : si erreur de malloc, calloc

	- char **envp : list des var d'env sous forme ["v1=v2", ..., 0]

	Fonction a utiliser pour execve
	=> il faut passer comme arg a execve une liste de vairbales d'environnement
	=> sous la forme ["v1=v2", ..., 0]

*/
char	**get_envp(t_env_vars *vars)
{
	t_env_vars	*tmp;
	char		**envp;
	int			i;

	i = 0;
	tmp = vars;
	while (tmp != NULL)
	{
		i ++;
		tmp = tmp -> next;
	}
	envp = ft_calloc(i + 2, sizeof(char *));
	if (!vars || !envp)
		return (NULL);
	i = 0;
	tmp = vars;
	while (tmp != NULL)
	{
		envp[i] = join_name_value(tmp);
		if (envp[i++] == 0)
			return (free_tab(envp), NULL);
		tmp = tmp -> next;
	}
	return (envp);
}
