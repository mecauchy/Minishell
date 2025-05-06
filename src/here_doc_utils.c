/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:19:49 by vluo              #+#    #+#             */
/*   Updated: 2025/05/07 01:12:54 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_hd(t_here_doc *hd)
{
	free(hd -> delimiter);
	free_tab(hd -> cmd_args -> arr);
	free(hd -> cmd_args);
	free(hd);
}

static void	parse_cmd_args(char **cmd, t_here_doc *hd, int deli)
{
	int	i;

	i = deli;
	while (--i >= 0)
	{
		hd->cmd_args->arr = append(hd->cmd_args->arr, &hd->cmd_args->tot_len,
				&hd->cmd_args->arr_i, ft_strdup(cmd[i]));
		if (!hd->cmd_args->arr)
			return (free(hd -> delimiter),
				free_tab(hd->cmd_args->arr), free(hd));
	}
	i = deli + 1;
	while (cmd[++i])
	{
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
	int			deli;
	int			i;

	hd = ft_calloc(1, sizeof(t_here_doc));
	if (hd == 0)
		return (NULL);
	hd->cmd_args = init_array();
	hd -> fd = 0;
	i = -1;
	while (cmd[++i])
		if (!ft_strncmp(cmd[i], "<<", 3))
			break ;
	deli = i;
	hd -> delimiter = ft_strdup(cmd[deli + 1]);
	if (deli != 0)
		hd -> fd = ft_atoi(cmd[deli - 1]);
	parse_cmd_args(cmd, hd, deli);
	if (!hd)
		return (hd);
	corr = get_correct_cmd(hd->cmd_args->arr[0], mini);
	if (corr)
		return (free(hd->cmd_args->arr[0]), hd->cmd_args->arr[0] = corr, hd);
	return (hd);
}
