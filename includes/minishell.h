/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:02:17 by vluo              #+#    #+#             */
/*   Updated: 2025/04/21 18:48:11 by vluo             ###   ########.fr       */
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

# define HD_ERROR_MESSAGE "\nbash: warning: here-document \
delimited by end-of-file (wanted `%s')\n"

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
# include <signal.h>
# include <bits/types/siginfo_t.h>
# include <sys/wait.h>

extern int	g_signal;

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
}	t_cmd;

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

typedef struct s_mini
{
	struct sigaction	*sa;
	t_env_vars			*env_vars;
	int					exit_status;
}	t_mini;

typedef struct s_here_doc
{
	char	**cmd_args;
	int		fd;
	char	*delimiter;
	int		do_expand;
}	t_here_doc;

/* UTILS */

int					is_correctly_quoted(char *line);
int					is_all_space(char *line);
int					ft_is_identifier(char *name);
void				free_tab(char **tab);
char				*ft_strjoin_free(char *s1, char *s2);
char				**split_cmds(char *line);
char				**split_expand(char	**splited_cmds, char *line,
						t_env_vars *vars);
char				*get_correct_cmd(char *cmd);
char				**get_cmd_and_args(char *cmd,
						char **split_expanded, int index);
void				print_nonprintable(char *str);
void				wait_upex(int pid, t_env_vars *vars);
char				*get_last_arg(char **cmd_arg, t_env_vars *vars);
char				*unquote(char *line);

/* EXPAND */

char				*get_quote(char *line, t_env_vars *vars);
char				*get_env_var(char *line, t_env_vars *vars);
char				*expand(char *cmd, t_env_vars *vars);

/* MINI STRUCT FUNCTIONS */

t_mini				*init_mini(char **envp);
void				free_mini(t_mini *mini);

/* ENV_VARS STRUCT FUNCTIONS */

t_env_vars			*init_env_vars(char **envp);
char				*get_var_value(t_env_vars*vars, char *name);
int					vars_add(t_env_vars *vars, char *name, char *value);
void				vars_del_one(t_env_vars *vars, char *name);
void				free_vars(t_env_vars *vars);
char				**get_envp(t_env_vars *vars);

/* SIGNALS */

void				handle_ctrc_c(int sig);
struct sigaction	*init_ctrl_c_sig(void);

struct sigaction	*init_quit(void);

/* REDIRECTION*/

int					is_redir(char *cmd);
int					len_without_redir(char **cmd);
char				**clean_without_redir(char **cmd);

/* COVERT TO DEC */

int					octal_to_dec(char *octal);
int					hex_to_dec(char *nb);

/* BUILTINS */

void				ft_pwd(t_env_vars *vars);
void				ft_env(t_env_vars *vars);
void				ft_export(char **args, t_env_vars *vars);
void				ft_unset(char **args, t_env_vars *vars);
void				ft_exit(char **n, t_mini *mini);
void				ft_echo(char **args, t_env_vars *vars);
void				ft_cd(char *path, t_env_vars *vars);
int					is_builtin(char *cmd, char **cmd_args, t_mini *mini);

/* HERE DOC */

void				free_hd(t_here_doc *hd);
t_here_doc			*parse_heredoc(char *cmd);
void				here_doc_cmd(char *cmd, t_env_vars *vars);

/* MAIN */

void				exec_cmd(char *cmd, char **cmd_args, t_env_vars *vars);

#endif