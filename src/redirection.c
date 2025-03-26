/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy- <mcauchy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:12:52 by mcauchy-          #+#    #+#             */
/*   Updated: 2025/03/26 14:33:30 by mcauchy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*								------EXEC------

1/ TOKENISATION ->	decouper la ligne de cmd (**av) en tokens : 
					- mot (ex : cat), 
					- operateur (ex : >),
					- fichier || delimiteur (ex: file.txt || stop)
					le delimiteur c'est dans le cas ou l'operateur est un 
					heredoc donc cela correspondra a sa condition d'arret mais 
					pr le moment le but est de tout classer, pas d'executer
				
			1/		CREE 1ERE FONCTION qui parcours les tokens un a un, 
					si on tombe sur un delimiteur alors on cree / alloue
					notre structure t_redir, -- if (is_redir()) ....
					
			2/		CREE 2E FONCTION is_redir(); qui vas definir un (int)type
					en fonction de l'operateur
					
				->	Les operateurs de redirection et les fichiers doivent etre 
					liees sauf en cas de probleme ce sera toujours le +1
			
			3/		CREE 3E FONCTION qui ajoute a char *file l'arg + 1 si il 
					existe car comme je l'ai dit precedement 
					les OP/FICHIERS sont toujours liees

				
2/ HEREDOCS		->	Lire l'entree standart jusqu'a rencontrer le delimiteur
					pour cela il faut cree un fichier temporaire pour stocker
					le contenu qui a ete lu


		---------------------EXEMPLE DE PARSING------------------------

				
	Commande : cat << EOF > output.txt < input.txt

  	Tokens : ["cat", "<<", "EOF", ">", "output.txt", "<", "input.txt"]

    Résultat :

	args : ["cat"]

	redirs :

	FONCTION ADD_REDIR(T_CMD *CMD, INT TYPE, CHAR *FILE)
---	t_redir *new_redirs = malloc(sizeof(t_redir))
---	nredir.type = type
--- nredir.file = file
--- nredir.next = cmd.redir 
--- cmd.redir = nredir
	
	Ce qui permetera d'avoir un beau tableau avec toutes ces donees 

	type = <<, file = "EOF"

	type = >, file = "output.txt"

	type = <, file = "input.txt"

	
	----- ATTENTION 
	
	--	dans le cas ou il y a plusieurs redirections (>) 
		exemple : ... > file_1 > file_2
		Seul File_2 sera utilise, il faut faire attention a l'ordre pour 
		eviter que ca se chevauche

	--	dabs le cas ou le delimiteur HEREDOC n'est pas trouve
		ex : cat << EOF --> sans EOF final
		
	--	dans le cas ou le fichier n'est pas accesible 
		car il n'y a pas les droits
		ex : ~/document/file --> chmod 000 file
	
	----- GERER LE CAS OU
	
	--	Si la meme redirection est trouve plusieurs fois alors il faut 
		prioriser la derniere

	--	Nettoyer le fichier tmp HEREDOC apres l'execution de la cmd
*/

// param = recupere le char **cmd a l'index i -> cmd[i]
// renvoi 1 ou 0 pour pouvoir calcluer cb on a de redirection dans la ligne 
//	de cmd
// !!! CREE VRAI FONCTION FT_STRCMP
int	is_redir(char *cmd)
{
	if (strcmp(cmd, "<") == 0 || strcmp(cmd, ">") == 0
		|| strcmp(cmd, "<<") == 0 || strcmp(cmd, ">>") == 0)
		return (1);
	return (0);
}

/*
Cette fonction va boucler tant que cmd[i] existe afin de sauter toutes les 
redirection qu'elle aura trouver ce qui vas nous permettre de recyperer la
taille de la cmd sans les redirection en faisant i +=2 car 
comme on a pu le voir apres chaque operateur on a le fichier / delimiteur
Bien penser a break si cmd[i] n'existe plus car en faisant i+=2 on peut 
car on peut avoir des depassements
Sinon on incremente notre count qui sera la taille sans delimiteurs ... 
ou -1 en cas de pb
*/
int	len_without_redir(char **cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (is_redir(cmd[i]))
		{
			i += 2;
			if (!cmd[i])
				break ;
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

/*
cette fonction a pour but principal de recuperer la chaine 
sans redir / fichier (avec i+=2) et de stocker grace a strdup
la char **nouvelle_cmd qu'on a pu alloue avec nb_of_redir(cmd) + 1 
donc en vrai ces deux fonctions ont a peu pres les memes conditions
c'est juste que l'une calcule et l'autre stock
(besoin d'un int j pour recup uniquement ce dont on a besoin pour **new_cmd)

--- 						COMMANDE ORIGINALE

		["ls", ">>", "file.txt", "-l", "<", "input.txt", "|", "grep", "test"]

--- 					COMMANDE APRES CLEAN_WITHOUT_REDIR

		["ls", "-l", "|", "grep", "test"]

*/
char	**clean_without_redir(char **cmd)
{
	char	**new_cmd;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = len_without_redir(cmd);
	new_cmd = (char **)malloc(sizeof(char) * len);
	if (!new_cmd)
		return (NULL);
	while (cmd[i])
	{
		if (is_redir(cmd[i]))
		{
			// if (cmd[i + 2])
			i += 2;
			if (!cmd[i])
				break ;
		}
		else
		{
			new_cmd[j] = ft_strdup(cmd[i]);
			printf("\n [0%d]\t\t[  '%s'  ], \n", j, new_cmd[j]);
			j++;
			i++;
		}
	}
	new_cmd[len] = NULL;
	return (new_cmd);
}

int	count_redir(char **cmd)
{
	int	i;
	int	redir;

	i = 0;
	redir = 0;
	while (cmd[i])
	{
		if (is_redir(cmd[i]))
			redir++;
		i++;
	}
	return (redir);
}

// void	stock_redir(t_cmd *cmd, char **av)
// {
// 	int	redir;
// 	int	i = 0;

// 	redir = count_redir(av);
// 	while(redir > 0 && av[i])
// 	{
// 		if (is_redir(av[i]) && av[i])
// 		{
// 			cmd->redirs->type = av[i];
// 			printf("type is -> [ %s ] \n", cmd->redirs->type);
// 			cmd->redirs->file = av[i + 1];
// 			printf("the file/ delmiter is -> %s\n", cmd->redirs->file);
// 			redir--;
// 			i += 2;
// 			cmd->redirs = cmd->redirs->next;
// 			if (!av[i])
// 				break ;
// 		}
// 		else
// 			i++;
// 	}
// }

// void	stock_line(char **av)
// {
// 	if (count_redir >= 1)
// 		stock_redir(av);
// }

/*
recuperer lst->token->cmd dans le main dans le parsing
*/

/*
Cette fonction a pour but de stocker les informations recu en ligne de 
commande (pour le moment dans un tableau mais le but sera d'utliser t_cmd *cmd)
ce qui nous permettra d'avoir notre type et le file correspondant.
Pour cela j'ai decide de checker le nb de redirection total garce a la fonction
count_redir().
Voici la sortie pour le moment : 
type is -> [ << ] 
the file/ delmiter is -> EOF
type is -> [ > ] 
the file/ delmiter is -> output.txt
type is -> [ < ] 
the file/ delmiter is -> input.txt
*/
void	stock_redir(char **av)
{
	int		redir;
	int		i = 0;
	int		j = 0;
	char	**type;
	char	**file;

	redir = count_redir(av);
	type = (char **)malloc(sizeof(char) * redir + 1);
	if (!type)
		return ;
	file = (char **)malloc(sizeof(char) * redir + 1);
	if (!file)
		return ;
	while (redir > 0 && av[i])
	{
		if (is_redir(av[i]) && av[i])
		{
			type[j] = ft_strdup(av[i]);
			printf("type is -> [ %s ] \n", type[j]);
			file[j] = ft_strdup(av[i + 1]);
			printf("the file/ delmiter is -> %s\n", file[j]);
			redir--;
			i += 2;
			j++;
			if (!av[i])
				break ;
		}
		else
			i++;
	}
	type[redir + 1] = NULL;
}

/*
Pour l'instant ft_exec() me permet juste de tester que j'ai cree
	elle a pas de but clair pr le moment
*/
void	ft_exec(char **av)
{
	int		redir;
	char	**wo_redir;

	redir = count_redir(av);
	printf("nb of redir is = %d\n", redir);
	wo_redir = clean_without_redir(av);
	if (redir >= 1)
		stock_redir(av);
}

void	free_str(char **cmd)
{
	int	i = 0;

	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		i;

	dup = malloc((strlen(s) + 1) * sizeof(char));
	if (dup == 0)
		return (0);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i ++;
	}
	dup[i] = '\0';
	return (dup);
}

// int	main(int ac, char **av)
// {
// 	t_cmd	*cmd;
// 	ft_exec(av + 1);
// 	return (0);
// }

// int	main(int ac, char **av)
// {
// 	char	**cmd;
// 	int		res = 0;
// 	int		i = 0;
// 	char	**new_cmd;
// 	cmd = av + 1;
// 	res = len_without_redir(cmd);
// 	printf("\n--[	LEN WITHOUT REDIRECTION	== %d	]--\n \n", res);
// 	new_cmd = clean_without_redir(cmd);
// 	printf("\n\n");
// 	// free_str(new_cmd);
// 	return (0);
// }