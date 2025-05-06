/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:27:33 by mcauchy-          #+#    #+#             */
/*   Updated: 2025/05/06 22:26:32 by vluo             ###   ########.fr       */
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
			fd = open(redir[i][r_i]->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (perror("Minishell : open"), exit(EXIT_FAILURE));
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
	}
}

// void	redirection_right_right(t_redir *current)
// {
// 	int	fd;
// 	fd = open(current->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	if (fd == -1)
// 	{
// 		perror("Minishell : open");
// 		exit(EXIT_FAILURE);
// 	}
// 	else
// 	{
// 		dup2(fd, STDOUT_FILENO);
// 		close(fd);
// 	}
// }

// void	redirection_right(t_redir *redir)
// {
// 	int	fd;

// 	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd == -1)
// 	{perror("Minishell : open");
// 		exit(EXIT_FAILURE);
// 	}
// 	else
// 	{
// 		dup2(fd, STDOUT_FILENO);
// 		close(fd);
// 	}
// }

// void	redirection_left(t_redir *current)
// {
// 	int	fd;
// 	fd = open(current->file, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Minishell : open");
// 		exit(EXIT_FAILURE);
// 	}
// 	else
// 	{
// 		dup2(fd, STDIN_FILENO);
// 		close(fd);
// 	}
// }
