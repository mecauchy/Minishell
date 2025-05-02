/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:02:17 by vluo              #+#    #+#             */
/*   Updated: 2025/05/02 14:49:02 by vluo             ###   ########.fr       */
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
# define APPEND	">>"

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line_bonus.h"

#include <sys/types.h>
#include <sys/wait.h>

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <strings.h>
# include <unistd.h>
# include <fcntl.h>
// # include <linux/limits.h>
# include <limits.h>

/*
Comprend le file avec les delimiteurs stockees (type = <<, file = "output.txt")
struct s_redir	*next; -> Au cas ou il y a plusieurs redirections
*/
typedef struct s_redir
{
	char			*file;
	char			*type;
	// struct s_redir	*next;
}				t_redir;

typedef	struct s_array
{
	int		tot_len;
	int		arr_i;
	char	**arr;
}	t_array;

/*
Comprend la liste d'arguments (["ls", "-l" ">" ...])
Comprend la liste des redirections
*/
typedef struct s_cmd
{
	t_array	**args;
	t_redir	**redir;
}				t_cmd;

typedef struct s_data
{
	int		nb_cmds;
	// int		nb_heredocs;
	int		nb_pipes;
	int		*fd;
	int		*fdd;
	int		fd1[2];
	int		*pid;
	t_redir	*redir;
}				t_data;

/* REDIRECTION*/
int		is_redir(char *cmd);
int		len_without_redir(char **cmd);
void	clean_without_redir(t_cmd *cmd, char **old_cmd);

// void	apply_redirection(t_redir *redir);
void	redirection_left_left(t_redir *current);
void	redirection_left(t_redir *current);
void	redirection_right_right(t_redir *current);
void	redirection_right(t_redir *redir);


/* UTILS */

void	free_tab(char **tab);
char	*ft_strjoin_free(char *s1, char *s2);
char	**split_cmds(char *line);
char	*get_correct_cmd(char *cmd);

/* Expand */

char	*get_quote(char *line, char **envp);
char	*get_env_var(char *line, char **envp);
char	*expand(char *cmd, char **envp);

// test main fct //
void	ft_exec(t_cmd *cmd, char **av);
int		count_redir(char **cmd);
void	stock_redir(t_cmd **c, char **av);
void	apply_redirection(t_cmd *cmd, int i);
void	init_pids(t_data *data);
void	exec_multi_cmd(t_data **d, t_cmd *cmds, char **env);
void	redirect_pipe(t_data *data, int i);
void	wait_all_pids(t_data *data, int *s);
int		add_nb_cmd(char **av, t_data *data);
void	init_fds(t_data *data);
void	close_fds(t_data *data);

#endif