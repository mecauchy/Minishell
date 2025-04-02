/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy- <mcauchy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:41:49 by mcauchy-          #+#    #+#             */
/*   Updated: 2025/04/02 12:30:48 by mcauchy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirection_right(t_redir *redir)
{
	int	fd;
	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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

void	redirection_right_right(t_redir *current)
{
	int	fd;
	fd = open(current->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
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

void	redirection_left_left(t_redir *current)
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

// revoir utilite
// void	apply_redirection(t_redir *redir)
// {
// 	t_redir	*current;

// 	current = redir;
// 	while (current)
// 	{
// 		if (current->type == REDIR_OUT)
// 			redirection_right(current);
// 		else if (current->type == APPEND)
// 			redirection_right_right(current);
// 		else if (current->type == REDIR_IN)
// 			redirection_left(current);
// 		else if (current->type == HEREDOC)
// 			redirection_left_left(current);
// 		current = current->next;
// 	}
// }

// remplacer char **cmd par cmd->token[] separes a l'aide du pipe
void	help_redir(t_redir *redir)
{
	int	i;

	i = 0;
	if (redir->type[0] == '>')
	{
		if (redir->type[1] && redir->type[1] == '>')
			redirection_right_right(redir);
		else
			redirection_right(redir);
	}
	if (redir->type[0] == '<')
	{
		if (redir->type[1] == '<')
			redirection_left_left(redir);
		else
			redirection_left(redir);
	}
}