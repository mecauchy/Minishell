/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mecauchy <mecauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:31:13 by mecauchy          #+#    #+#             */
/*   Updated: 2025/04/09 14:41:48 by mecauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_pipe(char **av, int i)
{
	if (av[i][0] == '|' && (!av[i][1]))
		return (1);
	return (0);
}

void	add_nb_cmd_pipe(t_data *data, char **av)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while(av[i])
	{
		if (is_pipe(av, i))
			count++;
		i++;
	}
	if ((i - count) == 0)
		return ;
	data->nb_pipes = count;
}

int	add_nb_cmd(char **av, t_data *data)
{
	int	i;
	int	cmd;
	
	i = 0;
	cmd = 1;
	while (av[i])
	{
		i++;
	}
	i--;
	while (i >= 0)
	{
		while (i >= 0 && av[i][0] != '|')
			i--;
		if (i >= 0)
		{
			i--;
			cmd++;
		}
	}
	data->nb_cmds = cmd;
	return (cmd);
}

int	main(int ac, char **av)
{
	int		res;
	t_data	data;
	
	res = add_nb_cmd(av, &data);
	printf("nb de pipe == %d\n", res);
	printf("data->nb_cmds = %d\n", data.nb_cmds);
	return (0);
}