/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:51:40 by mcauchy-          #+#    #+#             */
/*   Updated: 2025/05/14 18:21:48 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_hd(t_cmd *cmds, int i)
{
	int	j;

	j = -1;
	while (cmds->args[i]->arr[++j])
	{
		if (ft_strncmp(cmds->args[i]->arr[j], "<<", 3) == 0)
			return (1);
	}
	return (0);
}

static void	exec_child(t_cmd *cmds, t_data *data, t_mini *m, int i)
{
	char	*corr_cmd;
	char	**env;

	signal(SIGQUIT, SIG_DFL);
	redirect_pipe(data, i);
	if (!cmds->args[i]->arr[0])
		exit(0);
	if (is_hd(cmds, i))
		return (here_doc_cmd(cmds->args[i]->arr, m, cmds, i),
			exit(ft_atoi(get_var_value(m->env_vars, "?"))));
	apply_redirection(cmds->redir, i);
	corr_cmd = get_correct_cmd(cmds->args[i]->arr[0], m);
	if (corr_cmd != NULL)
	{
		free(cmds->args[i]->arr[0]);
		cmds->args[i]->arr[0] = corr_cmd;
	}
	vars_add(m -> env_vars, "_", cmds->args[i]->arr[0]);
	if (is_builtin(cmds->args[i]->arr[0], cmds->args[i]->arr, m) != 1)
		return (env = get_envp(m->env_vars), execve(cmds->args[i]->arr[0],
				cmds->args[i]->arr, env), free_tab(env), exit(127));
	return (exit(ft_atoi(get_var_value(m->env_vars, "?"))));
}

void	exec_multi_cmd(t_data **d, t_cmd *cmds, t_mini *m)
{
	int		i;
	t_data	*data;

	i = 0;
	data = *d;
	while (i < data->nb_cmds)
	{
		if (!ft_strncmp(cmds->args[i]->arr[0], "exit", 5))
			exit_too_many_args(cmds->args[i]->arr, m);
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			exit(1);
		if (data->pid[i] == 0)
		{
			g_signal = SIGUSR1;
			return (exec_child(cmds, data, m, i));
		}
		i++;
	}
	close_fds(data);
	wait_all_pids(data, m -> env_vars, cmds);
}

int	multi_cmds(t_mini *mini)
{
	t_data	*data;
	t_cmd	*cmd;

	data = malloc(sizeof(t_data));
	data -> nb_cmds = nb_cmd(mini->cmds_splitted);
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
	exec_multi_cmd(&data, cmd, mini);
	free_cmds(cmd);
	free(data -> pid);
	free(data -> fd);
	free(data);
	return (0);
}
