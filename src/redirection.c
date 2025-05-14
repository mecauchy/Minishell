/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:27:33 by mcauchy-          #+#    #+#             */
/*   Updated: 2025/05/14 14:28:59 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	apply_redirection(t_redir ***redir, int i)
{
	int	fd;
	int	r_i;

	r_i = -1;
	while (redir[i][++r_i])
	{
		if (redir[i][r_i]->type == NULL)
			continue ;
		if (redir[i][r_i]->type[0] == '<')
		{
			fd = open(redir[i][r_i]->file, O_RDONLY);
			if (fd == -1)
				return (perror("Minishell : open"), exit(EXIT_FAILURE));
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		if (redir[i][r_i]->type[0] == '>')
		{
			if (redir[i][r_i]->type[1] == '>')
				redirection_right_right(redir, i, r_i);
			else
				redirection_right(redir, i, r_i);
		}
	}
}

void	redirection_right_right(t_redir ***redir, int i, int r_i)
{
	int	fd;

	fd = open(redir[i][r_i]->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror("Minishell : open"), exit(EXIT_FAILURE));
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redirection_right(t_redir ***redir, int i, int r_i)
{
	int	fd1;

	fd1 = open(redir[i][r_i]->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd1 == -1)
		return (perror("Minishell : open"), exit(EXIT_FAILURE));
	dup2(fd1, STDOUT_FILENO);
	close(fd1);
}
