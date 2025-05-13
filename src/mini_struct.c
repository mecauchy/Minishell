/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:06:52 by vluo              #+#    #+#             */
/*   Updated: 2025/05/13 16:26:10 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_mini	*init_mini(char **envp)
{
	t_mini	*mini;

	mini = ft_calloc(1, sizeof(t_mini));
	if (mini == 0)
		return (0);
	mini -> sas = init_sigs();
	mini -> env_vars = init_env_vars(envp);
	mini -> exit_status = 0;
	mini -> do_exit = 0;
	if (!(mini -> sas) || !(mini -> env_vars))
		return (free(mini -> sas), free_vars(mini -> env_vars), NULL);
	return (mini);
}

void	free_mini(t_mini *mini)
{
	free(mini -> sas[0]);
	free(mini -> sas[1]);
	free(mini -> sas);
	free_vars(mini -> env_vars);
	free(mini);
}
