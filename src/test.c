/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mecauchy <mecauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:38:43 by mecauchy          #+#    #+#             */
/*   Updated: 2025/04/29 16:05:11 by mecauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_pids(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmds)
	{
		data->pid[i] = -1;
		i++;
	}
}

void	init_fds(t_data *data)
{	
	int	i = 0;

	data->fd = malloc(sizeof(int) * (data->nb_cmds - 1) * 2);
	if (data->fd)
		return ;
	while (i < data->nb_cmds)
	{
		if ((pipe(data->fd + i) * 2) == -1)
		{
			perror("pipe");
			exit(1);
		}
		i++;
	}
}

void	close_fds(t_data *data)
{
	int	i = 0;
	
	while (i < data->nb_cmds - 1)
	{
		close(data->fd[i * 2]);
		close(data->fd[i * 2 + 1]);
		i++;
	}
}
void	redirect_pipe(t_data *data, int i)
{
	if (i == 0)
	{
		dup2(data->fd[1], STDOUT_FILENO);
	}
	else if (i == data->nb_cmds - 1)
	{
		dup2(data->fd[(2 * i) - 2], STDIN_FILENO);
	}
	else
	{
		dup2(data->fd[(2 * i) - 2], STDIN_FILENO);
		dup2(data->fd[(2 * i) + 1], STDOUT_FILENO);
	}
	// close_fds(data);
	close(data->fd[0]);
	close(data->fd[1]);
}

void	wait_all_pids(t_data *data, int *s)
{
	int	i;

	i = 0;
	while (i < data->nb_cmds)
	{
		waitpid(data->pid[i], s, 0);
		i++;
	}
}

// void	init_fds(t_data *data)
// {
// 	int	i = 0;
// 	while (i < data->nb_cmds - 1)
// 	{
// 		if (pipe(data->fd1) == -1)
// 		{
// 			perror("pipe");
// 			exit(1);
// 		}
// 		i++;
// 	}
// }

void	apply_redirection(t_redir *redir, t_data *data , int i)
{
	t_redir	*current;

	current = redir;
	if (!current)
		printf("NULL\n");
	if (i == 0)
	{
		int infd = open(current->file, O_RDONLY);
		if (infd == -1)
		{
			perror("Minishell : open");
			exit(EXIT_FAILURE);
		}
		else
		{
			dup2(infd, STDIN_FILENO);
			close(infd);
		}
	}
	else if (i == data->nb_cmds - 1)
	{
		current = current->next;
		int fd = open(current->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
}

void	redirection_right(t_redir *redir)
{
	int	file;
	
	file = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
	{
		perror("Minishell : open");
		exit(EXIT_FAILURE);
	}
	else
	{
		dup2(file, STDOUT_FILENO);
		close(file);
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

void	exec_multi_cmd(t_data **d, t_cmd *cmds, char **env)
{
	int i = 0;
	int	status = 0;
	t_data	*data;
	
	data = *d;
	printf("nb = %d\n", i);
	while (i < data->nb_cmds)
	{
		printf("boucle ith = %d\n", i);
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			exit(1);
		if (data->pid[i] == 0)
		{
			printf("PID = %d\n", getpid());
			printf("Child executing command: %s\n", cmds->args[i]);
			char **tmp = ft_split(cmds->args[i], ' ');
			redirect_pipe(data, i);
			apply_redirection(cmds->redirs, data, i);
			if (execve(tmp[0], tmp, env) == -1)
			{
				printf("ERRRRROR\n");
				exit(1);
			}
		}
		i++;
	}
	// close_fds(data);
	close(data->fd[0]);
	close(data->fd[1]);
	wait_all_pids(data, &status);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
}

int main(int ac, char **av, char **env) 
{
	t_data	*data;
	t_cmd	*cmd;

	t_redir *redir = malloc(sizeof(t_redir));
	cmd = malloc(sizeof(t_cmd));
	data = malloc(sizeof(t_data));
	ft_exec(cmd, av + 1);
	add_nb_cmd(av, data);
	printf("nb comand is = %d\n", data->nb_cmds);
	if (!redir || ac < 0)
		return (0);
	data->pid = malloc(sizeof(int) * data->nb_cmds);
	if (!data->pid)
	{
		perror("malloc");
		exit(1);
	}
	if (!data)
		return (0);
	init_fds(data);
	data->fd = malloc(sizeof(int) * (data->nb_cmds - 1) * 2);
	pipe(data->fd);
	exec_multi_cmd(&data, cmd, env);
    return (0);
}
