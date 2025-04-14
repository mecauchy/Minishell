/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy- <mcauchy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:38:43 by mecauchy          #+#    #+#             */
/*   Updated: 2025/04/14 17:08:01 by mcauchy-         ###   ########.fr       */
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
		dup2(data->fd[1], STDOUT_FILENO);
		close(data->fd[1]);
	}
	if (i < data->nb_cmds - 1)
		close(data->fd[0]);
	if (prev_infile != -1)
		close(prev_infile);
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
// void	exec_multi_cmd(t_data *data, t_cmd *cmd)
// {
// 	int	i;
// 	int	prev_infile;
// 	int	pipe_fd[2];

// 	prev_infile = -1;
// 	i = 0;
// 	if (pipe(pipe_fd) == -1)
// 	{
// 		perror("pipe");
// 		exit(1);
// 	}
// 	while (i < data->nb_cmds)
// 	{
// 		data->pid[i] = fork();
// 		if (data->pid[i] < 0)
// 		{
// 			perror("fork");
// 			exit(1);
// 		}
// 		if (data->pid[i])
// 		{
// 			redirect_pipe(data, prev_infile, i);
// 			apply_redirection(cmd[i].redirs);
// 			// EXECVP CMD[0] -> child_exec(data);
// 		}
// 		// parent process
// 		else
// 		{
// 			if (prev_infile != -1)
// 				close(prev_infile);
// 			prev_infile = data->fd[0];
// 			close(data->fd[1]);
// 		}
// 		i++;
// 	}
// 	wait_all_pids(data);
// }

int main(int ac, char **av) {
    // t_cmd cmds[2];
	// char	**res;
    // Première commande : ls -l

	if (ac > 0)
		ft_exec(av);
    // cmds[0].args = (char *[]){"ls", "-l", NULL};
    // cmds[0].redirs = NULL;

    // // Deuxième commande : grep ".c" > result.txt
    // cmds[1].args = (char *[]){"grep", ".c", NULL};
    // t_redir *redir = malloc(sizeof(t_redir));
    // redir->file = strdup("result.txt");
    // redir->type = REDIR_OUT;
    // redir->next = NULL;
    // cmds[1].redirs = redir;

    // // Exécuter le pipeline
    // execute_pipeline(cmds, 2);

    return 0;
}