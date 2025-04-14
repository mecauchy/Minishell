/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:11:07 by vluo              #+#    #+#             */
/*   Updated: 2025/04/14 15:45:02 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_correctly_quoted(char *line)
{
	int		i;
	char	c;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			c = line[i++];
			while (line[i] && line[i] != c)
				i ++;
			if (!line[i])
				return (0);
		}
	}
	return (1);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i ++]);
	free(tab);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len_s1;
	int		len_s2;
	char	*strj;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	strj = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (strj == 0)
		return (0);
	i = 0;
	j = 0;
	while (s1 && s1[i])
		strj[j ++] = s1[i ++];
	i = 0;
	while (s2 && s2[i])
		strj[j ++] = s2[i ++];
	strj[len_s1 + len_s2] = '\0';
	free(s1);
	free(s2);
	return (strj);
}

void	free_vars(t_env_vars *vars)
{
	if (vars != NULL)
	{
		free_vars(vars -> next);
		free(vars -> name);
		free(vars -> value);
		free(vars);
	}
}

void	print_nonprintable(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_isprint(str[i]))
			ft_printf("%c", str[i]);
		else if (str[i] == '\n')
			ft_printf("\\n");
		else if (str[i] == '\t')
			ft_printf("\\t");
		else if (str[i] == '\v')
			ft_printf("\\v");
		else if (str[i] == '\r')
			ft_printf("\\r");
		else if (str[i] == '\f')
			ft_printf("\\f");
	}
	ft_printf("\n");
}
