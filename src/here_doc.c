/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:57:52 by vluo              #+#    #+#             */
/*   Updated: 2025/05/07 01:18:26 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_lines(t_list *lines, t_here_doc *hd, t_env_vars *vars, int fd)
{
	t_list	*tmp;
	char	*line;
	char	*to_ex;

	vars_add(vars, "?", "0");
	if (hd -> cmd_args == 0)
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
		write(fd, line, ft_strlen(line));
		free(line);
		tmp = tmp -> next;
	}
	ft_lstclear(&lines, free);
}

static t_list	*get_del_lines(char *deli, t_env_vars *vars)
{
	char	*lin;
	char	*unquo_del;
	t_list	*lines;

	lines = NULL;
	unquo_del = unquote(deli);
	ft_putstr_fd("heredoc> ", 1);
	lin = get_next_line(0);
	while (lin && !(!ft_strncmp(lin, unquo_del, ft_strlen(unquo_del))
			&& lin[ft_strlen(unquo_del)] == '\n'))
	{
		ft_lstadd_back(&lines, ft_lstnew(lin));
		ft_putstr_fd("> ", 1);
		lin = get_next_line(0);
	}
	if ((lin == NULL || ft_strncmp(lin, unquo_del, ft_strlen(unquo_del))) != 0
		&& g_signal == SIGUSR1)
	{
		vars_add(vars, "_", "");
		return (printf(HD_ERROR_MESSAGE, deli), free(unquo_del), lines);
	}
	if (!lin)
		return (ft_lstclear(&lines, free), free(unquo_del), NULL);
	return (free(lin), free(unquo_del), lines);
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
		print_lines(lines, hd, vars, f_id[1]);
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
		if (is_builtin(hd->cmd_args->arr[0], hd->cmd_args->arr, mini))
			return (ft_atoi(get_var_value(mini->env_vars, "?")));
		vars_add(mini -> env_vars, "_", hd->cmd_args->arr[0]);
		return (envp = get_envp(mini->env_vars),
			execve(hd->cmd_args->arr[0], hd->cmd_args->arr, envp),
			printf("%s: command not found\n", hd->cmd_args->arr[0]),
			free_tab(envp), close(f_id[0]), exit(127), 127);
	}
	return (_value = get_last_arg(hd->cmd_args->arr, mini -> env_vars),
		vars_add(mini -> env_vars, "_", _value), free(_value), pid2);
}

void	here_doc_cmd(char **cmd, t_mini *mini)
{
	t_here_doc	*hd;
	t_list		*lines;
	int			f_id[2];
	int			ps[2];

	hd = parse_heredoc(cmd, mini);
	if (hd == 0)
		return ;
	lines = get_del_lines(hd -> delimiter, mini -> env_vars);
	if (lines == 0 && g_signal != SIGUSR1)
		return (vars_add(mini -> env_vars, "?", "130"), free_hd(hd));
	if (hd -> cmd_args == 0)
		return (print_lines(lines, hd, mini->env_vars, hd->fd), free_hd(hd));
	if (pipe(f_id) == -1)
		return (free_hd(hd), ft_lstclear(&lines, free));
	ps[0] = hd_pr_lines(hd, f_id, lines, mini -> env_vars);
	ps[1] = hd_exec_cmd(hd, f_id, mini);
	if (ps[0] == -1 || ps[1] == -1)
		return (free_hd(hd), ft_lstclear(&lines, free));
	return (close(f_id[0]), close(f_id[1]),
		wait_upex(ps[0], mini->env_vars, hd->cmd_args->arr),
		wait_upex(ps[1], mini->env_vars, hd->cmd_args->arr),
		ft_lstclear(&lines, free), free_hd(hd));
}
