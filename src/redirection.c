/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy- <mcauchy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:27:33 by mcauchy-          #+#    #+#             */
/*   Updated: 2025/05/06 13:29:58 by mcauchy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	apply_redirection(t_cmd *cmd, int i)
{
	int	fd;

	if (cmd->redir[i]->type == NULL)
		return ;
	if (cmd->redir[i]->type[0] == '<')
	{
		fd = open(cmd->redir[i]->file, O_RDONLY);
		if (fd == -1)
			return (perror("Minishell : open"), exit(EXIT_FAILURE));
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (cmd->redir[i]->type[0] == '>')
	{
		fd = open(cmd->redir[i]->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (perror("Minishell : open"), exit(EXIT_FAILURE));
		dup2(fd, STDOUT_FILENO);
		close(fd);
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
