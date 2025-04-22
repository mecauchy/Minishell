/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:05:16 by vluo              #+#    #+#             */
/*   Updated: 2025/04/21 17:44:25 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* join_word manuel

	//Fonction a ne pas utiliser !!
	//Sert seulement a la fonction expand

	fonction permet de strjoin le debut de la chaine et le mot a expand

	ex : cmd = hello$l
	debut de chaine = hello
	join_word renvoie helloworld (si l == world)

	join_word renvoie alors l'indice apres le mot a expand
*/
static int	join_word(char *cmd, int start, char **joined, t_env_vars *vars)
{
	int		i;
	char	c;

	i = start;
	if (cmd[i] == '\'' || cmd[i] == '"')
	{
		*joined = ft_strjoin_free(*joined, get_quote(&cmd[i], vars));
		c = cmd[i ++];
		while (cmd[i] && cmd[i] != c)
			i ++;
		i ++;
	}
	else
	{
		*joined = ft_strjoin_free(*joined, get_env_var(&cmd[i], vars));
		while (cmd[i] && (cmd[i] != '\'' && cmd[i] != '"'))
			i ++;
	}
	return (i);
}

/* Expand manuel

Arguments :

	- vars : est le dictionnaire dont on a stockees toutes 
	les variables d'enrinnement

	- cmd = la commande a expand 
	ex : tu rentres ->  minishell> "$PWD " exemple ...
	avant de expand on va split selon ' '(espace) -> ce qui donne un tableau
		avec ["$PWD ", exemple, ...]
	(pour split ce sera surement gerer avant dans parse_line (a ameliorer))
	expand va alors prendre le 1er element :
		"$PWD " (qui est donc notre argument cmd)
	cmd = "$PWD"

Valeurs de retour :

	expand(cmd, vars) renvoie alors la commande :
	- sans les "" et les ''
	- et la bonne variable d'environement (si cmd contient un $)
	ex : expand("pwd", vars) renvoie => pwd
		 expand("$var_existe", vars) renvoie => valeur (si la variable
		 d'env var_existe = valeur)

	cas particulier :
	- si cmd ne contient ni "" ni '' ni $ alors expand renvoie une copie de cmd
	- expand peut renvoyer NULL 
		-> ce cas correspond a si cmd = "" ou cmd = ''
		-> ou cmd = $l (où l n'est associe a aucune variable d'enironnement)

	expand renvoie tjs quelque chose qu'il faut free apres utilisation

(Cette fonction est une foction principale qui regroupe unquote et get_env_var
si on veut evaluer une expr, qu'elle comporte un "", '' ou $ ou aucun des 3
on utlise expand pour bien recup la bonne expression)
*/
char	*expand(char *cmd, t_env_vars *vars)
{
	int		i;
	int		st;
	char	*joined;

	i = 0;
	joined = ft_strdup("");
	while (cmd[i])
	{
		st = i;
		while (cmd[i] && (cmd[i] != '\'' && cmd[i] != '"' && cmd[i] != '$' ))
			i ++;
		if (!cmd[i])
			return (ft_strjoin_free(joined, ft_substr(cmd, st, i - st)));
		if (cmd[i] == '$' && !cmd[i + 1])
			return (free(joined), ft_strdup("$"));
		if (cmd[i + 1] && cmd[i + 1] == '"')
			i ++;
		if (!cmd[i])
			return (ft_strjoin_free(joined, ft_substr(cmd, st, i - st)));
		if (i != 0)
			joined = ft_strjoin_free(joined, ft_substr(cmd, st, i - st));
		i = join_word(cmd, i, &joined, vars);
	}
	return (joined);
}
