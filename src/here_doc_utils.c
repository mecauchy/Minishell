/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:19:49 by vluo              #+#    #+#             */
/*   Updated: 2025/05/16 15:40:30 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_list	*get_del_lines(char *deli, t_env_vars *vars)
{
	char	*lin;
	char	*unquo_del;
	t_list	*lines;

	lines = NULL;
	unquo_del = unquote(deli);
	ft_putstr_fd("heredoc> ", 0);
	lin = get_next_line(0);
	while (lin && !(!ft_strncmp(lin, unquo_del, ft_strlen(unquo_del))
			&& lin[ft_strlen(unquo_del)] == '\n'))
	{
		ft_lstadd_back(&lines, ft_lstnew(lin));
		ft_putstr_fd("> ", 0);
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

t_list	*get_all_dels(t_here_doc *hd, t_env_vars *vars)
{
	int		i;
	t_list	*lines;

	i = -1;
	lines = 0;
	while (hd -> delimiter -> arr[++i])
	{
		if (lines != 0)
			ft_lstclear(&lines, free);
		lines = get_del_lines(hd -> delimiter -> arr[i], vars);
		if (lines == 0 && g_signal != SIGUSR1)
			return (NULL);
	}
	return (lines);
}

static void	get_dels(char **cmd, t_here_doc *hd)
{
	int	i;

	hd -> delimiter = init_array();
	i = -1;
	while (cmd[++i])
	{
		if (!ft_strncmp(cmd[i], "<<", 3))
			hd->delimiter->arr = append(hd->delimiter->arr,
					&hd->delimiter->tot_len, &hd->delimiter->arr_i,
					ft_strdup(cmd[i++ + 1]));
	}
}

static void	parse_cmd_args(char **cmd, t_here_doc *hd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (!ft_strncmp(cmd[i], "<<", 3))
		{
			i += 1;
			continue ;
		}
		hd->cmd_args->arr = append(hd->cmd_args->arr, &hd->cmd_args->tot_len,
				&hd->cmd_args->arr_i, ft_strdup(cmd[i]));
		if (!hd->cmd_args->arr)
			return (free(hd -> delimiter),
				free_tab(hd->cmd_args->arr), free(hd));
	}
}

t_here_doc	*parse_heredoc(char **cmd, t_mini *mini)
{
	t_here_doc	*hd;
	char		*corr;

	hd = ft_calloc(1, sizeof(t_here_doc));
	if (hd == 0)
		return (NULL);
	hd->cmd_args = init_array();
	get_dels(cmd, hd);
	hd -> fd = 0;
	parse_cmd_args(cmd, hd);
	if (!hd)
		return (hd);
	corr = get_correct_cmd(hd->cmd_args->arr[0], mini);
	if (corr)
		return (free(hd->cmd_args->arr[0]), hd->cmd_args->arr[0] = corr, hd);
	return (hd);
}
