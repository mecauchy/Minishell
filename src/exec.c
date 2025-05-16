/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:51:40 by mcauchy-          #+#    #+#             */
/*   Updated: 2025/05/16 15:30:43 by vluo             ###   ########.fr       */
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
	if (data -> nb_cmds != 1)
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

void	exec_multi_cmd(t_data **d, t_cmd *cmds, t_mini *mini)
{
	int		i;
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
			g_signal = SIGUSR1;
			return (exec_child(cmds, data, mini, i));
		}
		i++;
	}
	close_fds(data);
	wait_all_pids(data, mini -> env_vars, cmds);
}

void	single_cmd(t_data **d, t_cmd *cmds, t_mini *mini)
{
	t_data	*data;
	int		pid;

	g_signal = SIGUSR1;
	data = *d;
	if (is_hd(cmds, 0))
		return (here_doc_cmd(cmds->args[0]->arr, mini, cmds, 0));
	if (check_is_main_builtin(cmds->args[0]->arr[0]))
	{
		apply_redirection(cmds->redir, 0);
		is_builtin(cmds->args[0]->arr[0], cmds->args[0]->arr, mini);
		return ;
	}
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		g_signal = 0;
		return (exec_child(cmds, data, mini, 0));
	}
	wait_upex(pid, mini -> env_vars,
		ft_split(cmds->args[0]->arr[0], ' '), 1);
}

int	multi_cmds(t_mini *mini)
{
	t_data	*data;
	t_cmd	*cmd;

	data = malloc(sizeof(t_data));
	data -> nb_cmds = nb_cmd(mini->cmds_splitted);
	data->pid = malloc(sizeof(int) * data->nb_cmds);
	if (!data->pid)
		return (perror("malloc"), exit(1), 1);
	if (!data)
		return (0);
	init_fds(data);
	cmd = get_cmds(mini->cmds_splitted);
	if (!cmd)
		return (0);
	if (data -> nb_cmds == 1)
		single_cmd(&data, cmd, mini);
	else
		exec_multi_cmd(&data, cmd, mini);
	return (free_cmds(cmd), free(data->pid), free(data->fd), free(data), 0);
}
