/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy- <mcauchy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:02:17 by vluo              #+#    #+#             */
/*   Updated: 2025/03/26 14:30:11 by mcauchy-         ###   ########.fr       */
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
# include <strings.h>
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
	// int		type;
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

/* REDIRECTION*/
int		is_redir(char *cmd);
int		len_without_redir(char **cmd);
char	**clean_without_redir(char **cmd);

/* UTILS */

void	free_tab(char **tab);
char	*ft_strjoin_free(char *s1, char *s2);
char	**split_cmds(char *line);
char	*get_correct_cmd(char *cmd);

/* Expand */

char	*get_quote(char *line, char **envp);
char	*get_env_var(char *line, char **envp);
char	*expand(char *cmd, char **envp);

#endif