/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:57:52 by vluo              #+#    #+#             */
/*   Updated: 2025/05/16 15:40:01 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_hd_lines(t_list *lines, t_here_doc *hd, t_env_vars *vars)
{
	t_list	*tmp;
	char	*line;
	char	*to_ex;

	vars_add(vars, "?", "0");
	if (hd -> cmd_args -> arr[0] == 0)
		return (ft_lstclear(&lines, free));
	tmp = lines;
	while (tmp != 0)
	{
		if (hd -> do_expand)
		{
			to_ex = ft_substr((char *)(tmp -> content), 0,
					ft_strlen((char *)(tmp -> content)) - 1);
			line = expand(to_ex, vars);
			line = ft_strjoin_free(line, ft_strdup("\n"));
			free(to_ex);
		}
		else
			line = ft_strdup((char *)(tmp -> content));
		write(0, line, ft_strlen(line));
		free(line);
		tmp = tmp -> next;
	}
	ft_lstclear(&lines, free);
}

static int	hd_pr_lines(t_here_doc *hd, int *f_id, t_list *lines,
		t_env_vars *vars)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		dup2(f_id[1], 1);
		close(f_id[0]);
		print_hd_lines(lines, hd, vars);
		close(f_id[1]);
		return (exit(0), 0);
	}
	return (pid);
}

static int	hd_exec_cmd(t_here_doc *hd, int *f_id, t_mini *mini)
{
	char	**envp;
	int		pid2;
	char	*_value;

	if (is_builtin(hd->cmd_args->arr[0], hd->cmd_args->arr, mini))
		return (ft_atoi(get_var_value(mini->env_vars, "?")));
	pid2 = fork();
	if (pid2 == -1)
		return (-1);
	if (pid2 == 0)
	{
		if (hd -> fd != -1)
		{
			dup2(f_id[0], hd -> fd);
			close(f_id[1]);
			close(f_id[0]);
		}
		vars_add(mini -> env_vars, "_", hd->cmd_args->arr[0]);
		return (envp = get_envp(mini->env_vars),
			execve(hd->cmd_args->arr[0], hd->cmd_args->arr, envp),
			free_tab(envp), close(f_id[0]), exit(127), 127);
	}
	return (_value = get_last_arg(hd->cmd_args->arr, mini -> env_vars),
		vars_add(mini -> env_vars, "_", _value), free(_value), pid2);
}

int	*pipe_exec(t_here_doc *hd, t_mini *mini, t_cmd *cmds, int i)
{
	t_list	*lines;
	char	*corr;
	int		*fs;
	int		*ps;

	lines = get_all_dels(hd, mini -> env_vars);
	if (lines == 0 && g_signal != SIGUSR1)
		return (vars_add(mini -> env_vars, "?", "130"), free_hd(hd), NULL);
	if (hd -> cmd_args -> arr[0] == 0)
		return (print_hd_lines(lines, hd, mini->env_vars),
			free_hd(hd), NULL);
	ps = ft_calloc(2, sizeof(int));
	fs = ft_calloc(2, sizeof(int));
	if (pipe(fs) == -1)
		return (free_hd(hd), ft_lstclear(&lines, free), fs);
	ps[0] = hd_pr_lines(hd, fs, lines, mini -> env_vars);
	ft_lstclear(&lines, free);
	corr = get_correct_cmd(hd->cmd_args->arr[0], mini);
	if (corr)
		return (apply_redirection(cmds->redir, i), ps[1] = hd_exec_cmd(hd, fs,
				mini), free(corr), close(fs[0]), close(fs[1]), free(fs), ps);
	return (ps[1] = hd_exec_cmd(hd, fs, mini), apply_redirection(cmds->redir,
			i), close(fs[0]), close(fs[1]), free(fs), ps);
}

void	here_doc_cmd(char **cmd, t_mini *mini, t_cmd *cmds, int i)
{
	t_here_doc	*hd;
	int			*ps;

	hd = parse_heredoc(cmd, mini);
	if (hd == 0)
		return ;
	ps = pipe_exec(hd, mini, cmds, i);
	if (ps == 0)
		return ;
	if (ps[0] == -1 || ps[1] == -1)
		return (free_hd(hd));
	return (
		wait_upex(ps[0], mini->env_vars, NULL, 0),
		wait_upex(ps[1], mini->env_vars,
			ft_split(hd->cmd_args->arr[0], ' '), 1),
		free_hd(hd), free(ps));
}
