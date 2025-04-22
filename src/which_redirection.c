/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy- <mcauchy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:41:49 by mcauchy-          #+#    #+#             */
/*   Updated: 2025/04/22 12:17:51 by mcauchy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirection_right(t_redir *redir)
{
	int	fd;
	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	printf("redir file == %s\n", redir->file);
	if (fd == -1)
	{
		perror("Minishell : open");
		exit(EXIT_FAILURE);
	}
	else
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}


void	redirection_left(t_redir *current)
{
	int	fd;
	fd = open(current->file, O_RDONLY);
	if (fd == -1)
	{
		perror("Minishell : open");
		exit(EXIT_FAILURE);
	}
	else
	{
		dup2(fd, STDIN_FILENO);
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


// void	redirection_left_left(t_redir *current)
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

void	apply_redirection(t_redir *redir)
{
	t_redir	*current;

	current = redir;
	if (!current)
		printf("NULL\n");
	while (current)
	{
		if (current->type[0] == '>')
			redirection_right(current);
		// else if (current->type == APPEND)
		// 	redirection_right_right(current);
		else if (current->type[0] == '<')
			redirection_left(current);
		// else if (current->type == HEREDOC)
		// 	redirection_left_left(current);
		current = current->next;
	}
}
