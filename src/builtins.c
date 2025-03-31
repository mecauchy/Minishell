/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:29:00 by vluo              #+#    #+#             */
/*   Updated: 2025/03/31 12:31:22 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_path(void)
{
	ft_printf("getenv : %s\n", getenv("PWD"));
}

void	print_env(t_env_vars *vars)
{
	t_env_vars	*tmp;

	tmp = vars;
	while (tmp -> next != NULL)
	{
		ft_printf("%s=%s\n", tmp -> name, tmp -> value);
		tmp = tmp -> next;
	}
}
