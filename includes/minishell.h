/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:02:17 by vluo              #+#    #+#             */
/*   Updated: 2025/03/26 17:13:20 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define CYAN		"\033[1;96m"
# define RESET		"\033[0m"
# define RED		"\033[1;31m"
# define GREY 		"\033[0;90m"

# define REDIR_IN	"<"
# define REDIR_OUT	">"
# define HEREDOC	"<<"
# define O_APPEND	">>"

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line_bonus.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <linux/limits.h>
# include <limits.h>

/*
Comprend le file avec les delimiteurs stockees (type = <<, file = "output.txt")
struct s_redir	*next; -> Au cas ou il y a plusieurs redirections
*/
typedef struct s_redir
{
	char			*file;
	char			*type;
	struct s_redir	*next;
}				t_redir;

/*
Comprend la liste d'arguments (["ls", "-l" ">" ...])
Comprend la liste des redirections
*/
typedef struct s_cmd
{
	char	**args;
	t_redir	*redirs;
}				t_cmd;

/*
Dictionnaire stockant la liste des variables d'environnement
cle : name (nom de la variable d'env)
valeur : valeur de la variable
*/
typedef struct s_env_vars
{
	char				*name;
	char				*value;
	struct s_env_vars	*next;
}	t_env_vars;

/* REDIRECTION*/
int			is_redir(char *cmd);
int			len_without_redir(char **cmd);
char		**clean_without_redir(char **cmd);

/* UTILS */

void		free_tab(char **tab);
char		*ft_strjoin_free(char *s1, char *s2);
char		**split_cmds(char *line);
char		*get_correct_cmd(char *cmd);

/* ENV_VARS STRUCT FUNCTION */

t_env_vars	*init_var(char *name, char *value);
void		vars_add_one(t_env_vars *vars, char *name, char *value);
t_env_vars	*init_env_vars(char **envp);
char		*get_var_value(t_env_vars*vars, char *name);
void		free_vars(t_env_vars *vars);

/* EXPAND */

char		*get_quote(char *line, t_env_vars *vars);
char		*get_env_var(char *line, t_env_vars *vars);
char		*expand(char *cmd, t_env_vars *vars);

#endif