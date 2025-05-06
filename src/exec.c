/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:51:40 by mcauchy-          #+#    #+#             */
/*   Updated: 2025/05/06 22:27:04 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_multi_cmd(t_data **d, t_cmd *cmds, t_mini *m)
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
			printf("Child executing command: %s\n", cmds->args[i]->arr[0]);
			redirect_pipe(data, i);
			apply_redirection(cmds->redir, i);
			if (!cmds->args[i]->arr[0])
				exit(0);
			if (is_builtin(cmds->args[i]->arr[0], cmds->args[i]->arr, m))
				exit(ft_atoi(get_var_value(m->env_vars, "?")));
			vars_add(m -> env_vars, "_", cmds->args[i]->arr[0]);
			return (env = get_envp(m->env_vars), execve(cmds->args[i]->arr[0],
					cmds->args[i]->arr, env), exit(127));
		}
		i++;
	}
	close_fds(data);
	wait_all_pids(data, m -> env_vars, cmds);
}

void	print_cmds(t_cmd *cmd, t_mini *mini)
{
	int	i;
	int	j;

	i = -1;
	printf("------------------\n");
	while (++i < nb_cmd(mini->cmds_splitted))
	{
		printf("cmd [%d] : [ ", i);
		j = -1;
		while (cmd->args[i]->arr[++j])
			printf("%s ", cmd->args[i]->arr[j]);
		if (!cmd->redir[i][0])
			printf("] with no redirs \n");
		else
			printf("] with redirs \n");
		j = -1;
		while (cmd->redir[i][++j])
			printf("redir type = [%s] and file = [%s]\n",
				cmd->redir[i][j]->type, cmd->redir[i][j]->file);
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
