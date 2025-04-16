/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy- <mcauchy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:38:43 by mecauchy          #+#    #+#             */
/*   Updated: 2025/04/16 15:41:48 by mcauchy-         ###   ########.fr       */
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

// // pas fini a revoir
// void	init_nb_fork(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	data->fd = malloc(sizeof(int) * ((data->nb_cmds - 1) * 2));
// 	if (data->fd)
// 		ft_error();
// 	while (i < data->nb_cmds)
// 	{
// 		if (pipe(data->fd + i * 2))
// 			ft_error();
// 		i++;
// 	}
// }

/*
Chaque enfant :

Redirige son STDIN depuis le pipe précédent

Redirige son STDOUT vers le pipe suivant (sauf le dernier)

fd[0] -> entree sauf pour la premiere commande 

*/ 

void	redirect_pipe(t_data *data, int prev_infile, int i)
{
	if (prev_infile != -1)
	{
		dup2(prev_infile, STDIN_FILENO);
		close(prev_infile);
	}
	if (i < data->nb_cmds - 1)
	{
		dup2(data->fd[i * 2 + 1], STDOUT_FILENO);
		close(data->fd[1 * 2 + 1]);
		close(data->fd[1 * 2]);
	}
}

void	wait_all_pids(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmds - 1)
	{
		wait(NULL);
		i++;
	}
}

void	exec_multi_cmd(t_data *data, t_cmd *cmds)
{
	int	i;
	int	prev_infile;

	prev_infile = -1;
	i = 0;
	while (i < data->nb_cmds)
	{
		if (i < data->nb_cmds - 1)
		{
			if (pipe(data->fd + i * 2) == -1)
			{
				perror("pipe");
				exit(1);
			}
		}
		data->pid[i] = fork();
		printf("here\n");
		if (data->pid[i] < 0)
		{
			perror("fork");
			exit(1);
		}
		if (data->pid[i] == 0)
		{
			redirect_pipe(data, prev_infile, i);
			apply_redirection(cmds[i].redirs);
			execvp(cmds[i].args[0], cmds[i].args);
			perror("execvp");
			exit(1);
			// EXECVP CMD[0] -> child_exec(data);
		}
		// parent process
		else
		{
			if (prev_infile != -1)
				close(prev_infile);
			if (i < data->nb_cmds -1)
			{				
				prev_infile = data->fd[i * 2];
				close(data->fd[i * 2 + 1]);
			}
		}
		i++;
	}
	wait_all_pids(data);
}

int main(char **av) 
{
    t_cmd cmds[2];
	t_data	*data;
	t_cmd	*cmd;
	// char	**res;
    // Première commande : ls -l
    t_redir *redir = malloc(sizeof(t_redir));
	cmd = malloc(sizeof(t_cmd));
	data = malloc(sizeof(t_data));
	ft_exec(cmd, av + 1);
	add_nb_cmd(av, data);
    if (!redir)
		return 0;
    // cmds[0].args = (char *[]){"ls", "-l", NULL};
    // cmds[0].redirs = NULL;
    // // Deuxième commande : grep ".c" > result.txt
    // cmds[1].args = (char *[]){"wc", NULL};
	// redir->file = strdup("result.txt");
    // redir->type = REDIR_OUT;
    // redir->next = NULL;
    // cmds[1].redirs = redir;
	init_pids(data);
	data->fd = malloc(sizeof(int) * data->nb_cmds - 1 * 2);
	data->pid = malloc(sizeof(int) * data->nb_cmds);
	if (!data->fd)
	{
		perror("malloc");
		exit(1);
	}
	data->nb_cmds = 2;
	if (!data)
		return (0);
	exec_multi_cmd(data, cmds);
    return 0;
}

int main(int ac, char **av) 
{
	if (ac < 0)
		return 0;
	t_cmd *cmd = malloc(sizeof(t_cmd));
	clean_without_redir(cmd, av);
    return 0;
}