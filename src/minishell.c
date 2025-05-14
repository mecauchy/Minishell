/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:07:38 by vluo              #+#    #+#             */
/*   Updated: 2025/05/14 17:37:12 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal;

void	parse_line(char *line, t_mini *mini)
{
	char	**full_cmd;

	if (!is_correct_cmds(line))
		return (write(2, "bash: syntax error\n", 19),
			vars_add(mini->env_vars, "?", "2"), (void)line);
	full_cmd = split_cmds(line);
	mini -> cmds_splitted = split_expand(full_cmd, mini->env_vars);
	free_tab(full_cmd);
	if (!mini -> cmds_splitted || !mini -> cmds_splitted[0])
		return (free_tab(mini->cmds_splitted));
	multi_cmds(mini);
	free_tab(mini->cmds_splitted);
}

void	handle_line(t_mini *mini, char *line)
{
	int	ex;

	if (g_signal == SIGUSR2)
	{
		g_signal = 0;
		vars_add(mini -> env_vars, "?", "130");
	}
	if (line == NULL)
		return (ex = ft_atoi(get_var_value(mini -> env_vars, "?")),
			printf("exit\n"), rl_clear_history(), free_mini(mini), exit(ex));
	if (*line && !is_all_space(line))
	{
		add_history(line);
		if (!is_correctly_quoted(line))
		{
			printf("Not correctly quoted\n");
			vars_add(mini -> env_vars, "?", "2");
		}
		else
			parse_line(line, mini);
	}
	free(line);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_mini	*mini;
	int		exit;

	if (argv[1])
		return (argc - argc + 1);
	mini = init_mini(envp);
	if (!mini)
		return (printf("Malloc error\n"), 1);
	while (1)
	{
		g_signal = 0;
		signal(SIGQUIT, SIG_IGN);
		line = readline("minishell> ");
		signal(SIGQUIT, handle_sigquit);
		handle_line(mini, line);
		if (mini -> do_exit)
			return (rl_clear_history(), exit = mini -> exit_status,
				free_mini(mini), exit);
	}
	return (0);
}
