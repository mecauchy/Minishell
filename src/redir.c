/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:38:43 by mecauchy          #+#    #+#             */
/*   Updated: 2025/05/02 17:01:25 by vluo             ###   ########.fr       */
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
	int	i;

	i = 0;
	data->fd = malloc(sizeof(int) * ((data->nb_cmds) * 2));
	if (!data->fd)
	{
		return ;
	}
	while (i < data->nb_cmds - 1)
	{
		if (pipe(data->fd + i * 2) == -1)
		{
			perror("pipe");
			exit(1);
		}
		i++;
	}
}

void	close_fds(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmds - 1)
	{
		close(data->fd[i * 2]);
		close(data->fd[(i * 2) + 1]);
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
	close_fds(data);
}

void	wait_all_pids(t_data *data, t_env_vars *vars)
{
	int	i;

	i = 0;
	while (i < data->nb_cmds)
	{
		wait_upex(data -> pid[i], vars);
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
// else if (current->type[0] )

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

void	exec_multi_cmd(t_data **d, t_cmd *cmds, t_mini *mini)
{
	int		i;
	char	**env;
	t_data	*data;

	i = 0;
	data = *d;
	while (i < data->nb_cmds)
	{
		printf("boucle ith = %d\n", i);
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			exit(1);
		if (data->pid[i] == 0)
		{
			printf("PID = %d\n", getpid());
			printf("Child executing command: %s\n", cmds->args[i]->arr[0]);
			redirect_pipe(data, i);
			apply_redirection(cmds, i);
			if (!cmds->args[i]->arr[0])
				exit(0);
			env = get_envp(mini -> env_vars);
			if (execve(cmds->args[i]->arr[0], cmds->args[i]->arr, env) == -1)
			{
				free_tab(env);
				printf("ERRRRROR\n");
				exit(1);
			}
		}
		i++;
	}
	close_fds(data);
	wait_all_pids(data, mini -> env_vars);
}

void	print_cmds(t_cmd *cmd, t_mini *mini)
{
	int	i;
	int	j;

	i = -1;
	while (++i < nb_cmd(mini->cmds_splitted))
	{
		printf("cmd [%d] : [", i);
		j = -1;
		while (cmd->args[i]->arr[++j])
			printf("|%s| ", cmd->args[i]->arr[j]);
		if (cmd->redir[i] == 0)
			printf("] with no redir\n");
		else
			printf("] with redir type = [%s] and file = [%s]\n",
				cmd->redir[i]->type, cmd->redir[i]->file);
	}
	printf("------------------\n");
}

int	multi_cmds(t_mini *mini)
{
	t_data	*data;
	t_cmd	*cmd;

	data = malloc(sizeof(t_data));
	data -> nb_cmds = nb_cmd(mini->cmds_splitted);
	printf("nb comand is = %d\n", data->nb_cmds);
	data->pid = malloc(sizeof(int) * data->nb_cmds);
	if (!data->pid)
	{
		perror("malloc");
		exit(1);
	}
	if (!data)
		return (0);
	init_fds(data);
	cmd = get_cmds(mini->cmds_splitted);
	if (!cmd)
		return (0);
	print_cmds(cmd, mini);
	exec_multi_cmd(&data, cmd, mini);
	free_cmds(cmd);
	free(data -> pid);
	free(data -> fd);
	free(data);
	return (0);
}
