/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_upex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:52:05 by vluo              #+#    #+#             */
/*   Updated: 2025/05/14 18:20:30 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*test_directory(char *path)
{
	struct stat	sb;

	if (!(path[0] == '/' || (path[0] == '.' && path[1] && path[1] == '/')))
		return (write(2, path, ft_strlen(path)),
			write(2, ": command not found\n", 20), ft_itoa(127));
	if (stat(path, &sb) != 0)
		return (write(2, "bash: ", 6), write(2, path, ft_strlen(path)),
			write(2, ": No such file or directory\n", 28), ft_itoa(127));
	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
		return (write(2, "bash: ", 6), write(2, path, ft_strlen(path)),
			write(2, ": Is a directory\n", 17), ft_itoa(126));
	return (write(2, "bash: ", 6), write(2, path, ft_strlen(path)),
		write(2, ": Permission denied\n", 20), ft_itoa(126));
}

char	*write_error(int stat, char **cmd_args)
{
	if (stat == 127)
	{
		if (cmd_args)
			return (test_directory(cmd_args[0]));
	}
	return (ft_itoa(stat));
}

/* wait_upex manuel

wait and update exit selon la valeur de retour du processus
-> si il y a eu une erreur echo $? pour voir la valeur de sortie

Arguments : 
	- pid : l'id du process dont on veut wait
	- vars : les variables d'environnement
*/

void	wait_upex(int pid, t_env_vars *vars, char **cmd_args, int do_free)
{
	int		status;
	char	*exit_status;

	g_signal = SIGUSR1;
	waitpid(pid, &status, 0);
	if (g_signal == SIGINT)
		exit_status = ft_itoa(128 + g_signal);
	else if (WIFEXITED(status))
		exit_status = write_error(WEXITSTATUS(status), cmd_args);
	else
	{
		exit_status = ft_itoa(128 + g_signal);
		if (g_signal == SIGUSR1)
			exit_status = ft_itoa(128 + 3);
	}
	if (cmd_args)
		vars_add(vars, "_", cmd_args[0]);
	if (do_free)
		free_tab(cmd_args);
	return (vars_add(vars, "?", exit_status), free(exit_status));
}
