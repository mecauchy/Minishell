/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:19:49 by vluo              #+#    #+#             */
/*   Updated: 2025/04/28 16:48:09 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_hd(t_here_doc *hd)
{
	free(hd -> delimiter);
	if (hd -> cmd_args)
		free_tab(hd -> cmd_args);
	free(hd);
}

static int	get_delimiter(char *cmd, t_here_doc *hd)
{
	int	i;
	int	j;

	i = ft_strlen(cmd);
	while (--i >= 0)
		if (cmd[i] == '<' || cmd[i] == ' ' || cmd[i] == '\t')
			break ;
	hd -> delimiter = ft_substr(cmd, i + 1, ft_strlen(cmd) - i);
	j = -1;
	while (hd -> delimiter[++j])
		if (hd -> delimiter[j] == '"' || hd -> delimiter[j] == '\'')
			hd -> do_expand = 0;
	while (i >= 0 && (cmd[i] == ' ' || cmd[i] == '\t'))
		i --;
	while (i >= 0 && (cmd[i] == '<'))
		i --;
	if (i + 1 == 0)
	{
		if ((!hd -> delimiter))
			return (free(hd), -2);
		hd -> fd = -1;
		hd -> cmd_args = 0;
		return (-1);
	}
	return (i + 1);
}

static int	get_fd(char *cmd, int end, t_here_doc *hd)
{
	int		i;
	char	*sub;

	i = end;
	while (--i >= 0)
		if (ft_isdigit(cmd[i]) == 0)
			break ;
	if (i == -1)
		sub = ft_substr(cmd, 0, end);
	else
		sub = ft_substr(cmd, i, end - i);
	if (sub == 0)
		return (free(hd -> delimiter), free(hd), -2);
	hd -> fd = ft_atoi(sub);
	if (i == -1)
	{
		hd -> cmd_args = 0;
		return (free(sub), -1);
	}
	return (free(sub), i);
}

static int	get_hd_cmd_args(char *cmd, int i, t_here_doc *hd)
{
	char	*sub;

	sub = ft_substr(cmd, 0, i + 1);
	if (is_all_space(sub))
		return (free(sub), hd -> cmd_args = 0, 0);
	if (sub == 0)
	{
		free(hd -> delimiter);
		free(hd);
		return (-1);
	}
	hd -> cmd_args = ft_split(sub, ' ');
	free(sub);
	if (!hd -> delimiter || !hd -> cmd_args)
	{
		free_hd(hd);
		return (-1);
	}
	sub = get_correct_cmd(hd -> cmd_args[0]);
	if (!sub)
		return (0);
	free(hd -> cmd_args[0]);
	hd -> cmd_args[0] = sub;
	return (0);
}

t_here_doc	*parse_heredoc(char *cmd)
{
	t_here_doc	*hd;
	int			i;

	hd = ft_calloc(1, sizeof(t_here_doc));
	if (hd == 0)
		return (NULL);
	hd -> do_expand = 1;
	i = get_delimiter(cmd, hd);
	if (i == -2)
		return (NULL);
	if (i == -1)
		return (hd);
	i = get_fd(cmd, i, hd);
	if (i == -1)
		return (hd);
	if (i == -2)
		return (NULL);
	i = get_hd_cmd_args(cmd, i, hd);
	if (i == -1)
		return (NULL);
	return (hd);
}
