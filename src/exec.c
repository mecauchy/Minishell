/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy- <mcauchy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:51:40 by mcauchy-          #+#    #+#             */
/*   Updated: 2025/05/06 13:25:28 by mcauchy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_multi_cmd(t_data **d, t_cmd *cmds, t_mini *mini)
{
	int		i;
	char	**env;
	t_data	*data;

	i = 0;
	data = *d;
	while (i < data->nb_cmds)
	{
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			exit(1);
		if (data->pid[i] == 0)
		{
/*			 printf("PID = %d\n", getpid());
			printf("Child executing command: %s\n", cmds->args[i]->arr[0]);*/
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
