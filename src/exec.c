/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy- <mcauchy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:38:43 by mecauchy          #+#    #+#             */
/*   Updated: 2025/04/24 16:30:11 by mcauchy-         ###   ########.fr       */
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

void	redirect_pipe(t_data *data, int prev_infile, int i)
{
	int	j = 0;
	(void)(prev_infile);
	if (i == 0)
	{
		printf("000001 === %d\n", (i * 2 + 1));
		dup2(data->fd[(i * 2 + 1)], STDOUT_FILENO);
		// close(data->fd[1]);
		// close(prev_infile);
	}
	else if (i == data->nb_cmds - 1)
	{
		printf("i == %d\n", i);
		printf("000002 === %d\n", (2 * i) - 2);
		dup2(data->fd[(2 * i) - 2], STDIN_FILENO);
		// close(data->fd[(2 * i) - 2]);
	}
	else
	{
		printf("000000003 == %d\n", (2 * i) - 2);
		printf("000000004 == %d\n", (2 * i) + 1);
		dup2(data->fd[(2 * i) - 2], STDIN_FILENO);
		dup2(data->fd[(2 * i) + 1], STDOUT_FILENO);
		// close(data->fd[i * 2 + 1]);
		// close(data->fd[i * 2]);
	}
	while (j < (data->nb_cmds - 1)* 2)
	{
		close(data->fd[j]);
		j++;
	}
	// close_fds(data);
}

void	wait_all_pids(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmds)
	{
		waitpid(data->pid[i], NULL, 0);
		i++;
	}
}

void	init_fds(t_data *data)
{
	int	i = 0;
	while (i < data->nb_cmds - 1)
	{
		if (pipe(data->fd + (i * 2)) == -1)
		{
			perror("pipe");
			exit(1);
		}
		i++;
	}
}

void	exec_multi_cmd(t_data *data, t_cmd *cmds)
{
	int	i;
	int	prev_infile;
	char	**tmp;

	prev_infile = -1;
	i = 0;
	while (i < data->nb_cmds)
	{
		printf("nb cmds == %d\n", data->nb_cmds);
		data->pid[i] = fork();
		printf("here\n");
		if (data->pid[i] < 0)
		{
			perror("fork");
			exit(1);
		}
		printf("0001-here\n");	
		if (data->pid[i] == 0)
		{
			tmp = ft_split(cmds->args[i], ' ');
			printf("cmd[%d] --> %s\n", i, tmp[0]);
			redirect_pipe(data, prev_infile, i);
			apply_redirection(cmds->redirs);
			// execvp(cmds[i].args[0], cmds[i].args);
			execvp(tmp[0], tmp);
			perror("execvp");
			exit(1);
		}
		// else
		// {
		// 	printf("002-here\n");
		// 	if (prev_infile != -1)
		// 		close(prev_infile);
		// 	if (i < data->nb_cmds -1)
		// 	{				
		// 		prev_infile = data->fd[i * 2];
		// 		// close(data->fd[i * 2 + 1]);
		// 	}
		// }
		i++;
	}
	// close(data->fd[0]);
	// close(data->fd[1]);	
	// close(data->fd[2]);
	int	j = 0;
	while ((j < data->nb_cmds - 1)* 2)
	{
		close(data->fd[j]);
		j++;
	}
	wait_all_pids(data);
}

int main(int ac, char **av) 
{
    // t_cmd cmds[3];
	t_data	*data;
	t_cmd	*cmd;
    // Première commande : ls -l
    t_redir *redir = malloc(sizeof(t_redir));
	cmd = malloc(sizeof(t_cmd));
	data = malloc(sizeof(t_data));
	ft_exec(cmd, av + 1);
	add_nb_cmd(av, data);
    if (!redir || ac < 0)
		return (0);
    // cmds[0].args = (char *[]){"ls", "-l", NULL};
    // cmds[0].redirs = NULL;
    // cmds[1].args = (char *[]){"grep zeee", NULL};
	// cmds[1].redirs = NULL;
    // // Deuxième commande : grep ".c" > result.txt
    // cmds[2].args = (char *[]){"wc", NULL};
	// redir->file = strdup("02.txt");
    // redir->type = REDIR_OUT;
    // redir->next = NULL;
    // cmds[2].redirs = redir;
	// init_pids(data);
	data->fd = malloc(sizeof(int) * ((data->nb_cmds - 1) * 2));
	data->pid = malloc(sizeof(int) * data->nb_cmds);
	if (!data->fd || !data->pid)
	{
		perror("malloc");
		exit(1);
	}
	if (!data)
		return (0);
	init_fds(data);
	exec_multi_cmd(data, cmd);
	printf("SORTI\n");
    return (0);
}

// int main(int ac, char **av) 
// {
// 	if (ac < 0)
// 		return 0;
// 	t_cmd *cmd = malloc(sizeof(t_cmd));
// 	clean_without_redir(cmd, av);
//     return 0;
// }