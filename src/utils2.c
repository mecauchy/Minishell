/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:21:27 by vluo              #+#    #+#             */
/*   Updated: 2025/04/11 15:00:29 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_all_space(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (!((8 <= line[i] && line[i] <= 13) || line[i] == 32))
			return (0);
	return (1);
}

int	ft_is_identifier(char *name)
{
	int	i;

	if (!name)
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 0;
	while (name[++i])
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
	return (1);
}
