/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mecauchy <mecauchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:11:07 by vluo              #+#    #+#             */
/*   Updated: 2025/04/09 14:46:51 by mecauchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
