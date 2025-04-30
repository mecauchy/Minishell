/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:19:49 by vluo              #+#    #+#             */
/*   Updated: 2025/04/29 13:50:04 by vluo             ###   ########.fr       */
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

static int	get_del(char *cmd, t_here_doc *hd)
{
	int		i;
	int		start;
	char	*delimiter;

	i = 0;
	while (cmd[i] && !ft_isalnum(cmd[i]))
		i ++;
	if (cmd[i - 1] == '\'' || cmd[i - 1] == '"')
		hd -> do_expand = 0;
	start = i;
	while (cmd[i] && ft_isalnum(cmd[i]))
		i ++;
	delimiter = ft_substr(cmd, start, i - start);
	if (!delimiter)
		return (free(hd), 0);
	hd -> delimiter = delimiter;
	return (1);
}

static int	get_fd(char *cmd, int redir, t_here_doc *hd)
{
	int		i;
	char	*sub;

	i = redir - 1;
	while (i >= 0 && ft_isdigit(cmd[i]))
		i --;
	if (i == redir -1)
		hd -> fd = 0;
	sub = ft_substr(cmd, i + 1, (redir - 1 - i));
	if (!sub)
		return (free(hd -> delimiter), free(hd), 0);
	hd -> fd = ft_atoi(sub);
	return (free(sub), 1);
}

static int	get_cmd_all(char *cmd, t_here_doc *hd, int redir, t_env_vars *vars)
{
	int		i;
	char	*s1;
	char	*s2;
	char	**split;

	i = redir - 1;
	if (i == -1)
		return (hd -> cmd_args = 0, 1);
	while (i >= 0 && ft_isdigit(cmd[i]))
		i --;
	while (i >= 0 && (cmd[i] == ' ' || cmd[i] == '\t'))
		i --;
	s1 = ft_substr(cmd, 0, i + 1);
	i = redir + 2;
	while (cmd[i] && !ft_isalnum(cmd[i]))
		i ++;
	while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\t')
		i ++;
	s2 = ft_substr(cmd, i, ft_strlen(cmd) - i);
	s1 = ft_strjoin_free(s1, s2);
	split = ft_split(s1, ' ');
	hd -> cmd_args = split_expand(split, s1, vars);
	if (!hd -> cmd_args)
		return (free(s1), free_tab(split), 0);
	return (free(s1), free_tab(split), 1);
}

t_here_doc	*parse_heredoc(char *cmd, t_mini *mini)
{
	t_here_doc	*hd;
	char		*corr_cmd;
	int			i;

	hd = ft_calloc(1, sizeof(t_here_doc));
	if (hd == 0)
		return (NULL);
	hd -> do_expand = 1;
	i = 0;
	while (cmd[i] && cmd[i] != '<')
		i ++;
	if (!get_del(&cmd[i], hd))
		return (NULL);
	if (!get_fd(cmd, i, hd))
		return (NULL);
	if (!get_cmd_all(cmd, hd, i, mini -> env_vars))
		return (free(hd -> delimiter), free(hd), NULL);
	if (hd -> cmd_args == 0)
		return (hd);
	corr_cmd = get_correct_cmd(hd -> cmd_args[0]);
	if (corr_cmd)
		return (free(hd -> cmd_args[0]), hd -> cmd_args[0] = corr_cmd, hd);
	return (hd);
}
