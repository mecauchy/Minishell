/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy- <mcauchy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:23:23 by mcauchy-          #+#    #+#             */
/*   Updated: 2025/04/28 13:29:49 by mcauchy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	nb_cmd(t_cmd *cmd)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd->args[i])
// 	{
// 		i++;
// 	}
// 	printf("nb de cmd == %d\n", i);
// 	return (i);
// }

// char	**extract_line(t_cmd *cmd, int start, int end)
// {
// 	int	i;

// 	start = 0;
// 	i = 0;
// 	cmd[i].redirs = malloc(sizeof(char *) * (end + 1));
// 	if (!cmd[i].redirs)
// 		return (NULL);
// 	while (i < end)
// 	{
// 		cmd[i].redirs = ft_strdup(cmd->args + i);
// 		i++;
// 	}
// }

// void	separate_cmd(t_data *data, char **av, t_cmd *cmd)
// {
// 	int	i;
// 	int	start;

// 	i = 0;
// 	start = 0;
// 	while (av[i])
// 	{
// 		if (strcmp(av[i], "|") == 0)
// 			extract_line()
// 	}
// }