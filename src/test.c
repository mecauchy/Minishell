/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:38:43 by mecauchy          #+#    #+#             */
/*   Updated: 2025/05/02 15:01:00 by vluo             ###   ########.fr       */
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
	int	i = 0;
	
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

char	**append(char **sp, int *len_tot, int *sp_i, char *sub)
{
	int		i;
	char	**split_double;

	if (sub == 0)
		return (free_tab(sp), NULL);
	if (*sp_i < *len_tot)
	{
		*sp_i += 1;
		return (sp[*sp_i - 1] = sub, sp);
	}
	split_double = ft_calloc((*len_tot * 2) + 1, sizeof(char *));
	if (!split_double)
		return (free_tab(sp), NULL);
	i = -1;
	while (sp[++i])
		split_double[i] = sp[i];
	return (split_double[i] = sub, split_double[i + 1] = 0,
		*len_tot = *len_tot * 2, *sp_i = i + 1, free(sp), split_double);
}

void	free_cmds(t_cmd *cmds)
{
	int	i;

	i = -1;
	while (cmds->args[++i])
	{
		if (cmds->args[i]->arr)
			free_tab(cmds->args[i]->arr);
		free(cmds->args[i]);
	}
	free(cmds->args);
	i = -1;
	while (cmds->redir[++i])
	{
		free(cmds->redir[i]->type);
		free(cmds->redir[i]->file);
		free(cmds->redir[i]);
	}
	free(cmds->redir);
	free(cmds);
}

int	nb_cmd(char **av)
{
	int	i;
	int	nb_cmd;

	nb_cmd = 0;
	i = -1;
	while (av[++i])
	{
		if (av[i][0] == '|')
			nb_cmd ++;
	}
	return (nb_cmd + 1);
}

t_array	*init_array(void)
{
	t_array *tab;

	tab = ft_calloc(1, sizeof(t_array));
	if (tab == 0)
		return (NULL);
	tab -> tot_len = 2;
	tab -> arr_i = 0;
	tab -> arr = ft_calloc(3, sizeof(char *));
	if (tab -> arr == 0)
		return (free(tab), NULL);
	return (tab);
}

t_cmd	*init_cmds(int nb_cmd)
{
	t_cmd	*cmds;
	int		i;

	cmds = ft_calloc(1, sizeof(t_cmd));
	if (cmds == 0)
		return (NULL);
	cmds->args = ft_calloc(nb_cmd, sizeof(t_array *));
	cmds->redir = ft_calloc(nb_cmd, sizeof(t_redir *));
	if (!cmds->args || !cmds->redir)
		return (free(cmds->args), free(cmds->redir), free(cmds), NULL);
	i = -1;
	while (++i < nb_cmd)
	{
		cmds->args[i] = init_array();
		cmds->redir[i] = ft_calloc(1, sizeof(t_redir));
		if (!cmds->args[i] || !cmds -> redir[i])
			return (free_cmds(cmds), NULL);
	}
	return (cmds);
}

void	parse_cmds(t_cmd *cmds, char **av)
{
	int		i;
	int		nb_cmd;
	
	i = 0;
	nb_cmd = 0;
	while (av[i])
	{
		if (av[i][0] == '<' || av[i][0] == '>')
		{
			cmds->redir[nb_cmd]->type = ft_strdup(av[i++]);
			cmds->redir[nb_cmd]->file = ft_strdup(av[i++]);
			if (!cmds->redir[nb_cmd] || !cmds -> redir[nb_cmd])
				return (free_cmds(cmds));
		}
		if (!av[i])
			return ;
		if (av[i][0] == '|')
		{
			nb_cmd ++;
			i++;
		}
		if (av[i] && av[i][0] != '>' && av[i][0] != '<')
		{
			cmds->args[nb_cmd]->arr = append(cmds->args[nb_cmd]->arr,
						&cmds->args[nb_cmd]->tot_len,
						&cmds->args[nb_cmd]->arr_i, ft_strdup(av[i ++]));
			if (cmds->args[nb_cmd]->arr == 0)
				return (free_cmds(cmds));
		}
	}
}

t_cmd	*get_cmds(char **av)
{
	int		nb_cmds;
	t_cmd	*cmds;

	nb_cmds = nb_cmd(av);
	cmds = init_cmds(nb_cmds);
	if (!cmds)
		return (NULL);
	parse_cmds(cmds, av);
	if (!cmds)
		return (NULL);
	return (cmds);
}

void	apply_redirection(t_cmd *cmd, int i)
{
	if (cmd->redir[i]->type == NULL)
		return ;
	if (cmd->redir[i]->type[0] == '<')
	{
		int infd = open(cmd->redir[i]->file, O_RDONLY);
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
	if (cmd->redir[i]->type[0] == '>')
	{
		dprintf(1, "-----HHHHHEEERERRRREE\n");
		int fd = open(cmd->redir[i]->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
	// else if (current->type[0] )
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

void	redirection_right(t_redir *redir)
{
	int	fd;
	
	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{perror("Minishell : open");
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

void	exec_multi_cmd(t_data **d, t_cmd *cmds, char **env)
{
	int i = 0;
	int	status = 0;
	t_data	*data;
	
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
			// char **tmp = ft_split(cmds->args[i], ' ');
			redirect_pipe(data, i);
			apply_redirection(cmds, i);
			if (!cmds->args[i]->arr[0])
				exit(0);
			if (execve(cmds->args[i]->arr[0], cmds->args[i]->arr, env) == -1)
			{
				printf("ERRRRROR\n");
				exit(1);
			}
		}
		i++;
	}
	close_fds(data);
	wait_all_pids(data, &status);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
}

int main(int ac, char **av, char **env) 
{
	t_data	*data;
	t_cmd	*cmd;

	t_redir *redir = malloc(sizeof(t_redir));
	// cmd = malloc(sizeof(t_cmd));
	data = malloc(sizeof(t_data));
	// ft_exec(cmd, av + 1);
	// add_nb_cmd(av, data);
	data -> nb_cmds = nb_cmd(&av[1]);
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
	cmd = get_cmds(&av[1]);
	if (!cmd)
		return (0);
	int	i = -1;
	while (++i < nb_cmd(&av[1]))
	{
		printf("cmd [%d] : [", i);
		int	j = -1;
		while (cmd->args[i]->arr[++j])
			printf("|%s| ", cmd->args[i]->arr[j]);
		if (cmd->redir[i] == 0)
			printf("] with no redir\n");
		else
			printf("] with redir type = [%s] and file = [%s]\n",
				cmd->redir[i]->type, cmd->redir[i]->file);
	}
	printf("------------------\n");
	exec_multi_cmd(&data, cmd, env);
	free_cmds(cmd);
    return (0);
}
