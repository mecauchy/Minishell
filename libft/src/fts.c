/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:18:43 by vluo              #+#    #+#             */
/*   Updated: 2024/11/25 14:03:38 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	strschr(const char *s, char *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (set[j])
		{
			if (s[i] == set[j])
				return (i);
			j ++;
		}
		j = 0;
		i ++;
	}
	return (-1);
}

char	*ft_strcat(char *s1, char *s2)
{
	int		s1_length;
	int		s2_length;
	int		i;
	int		j;
	char	*res;

	s1_length = ft_strlen(s1);
	s2_length = ft_strlen(s2);
	res = malloc((s1_length + s2_length + 1) * sizeof(char));
	if (res == 0)
		return (0);
	i = 0;
	while (i < s1_length)
	{
		res[i] = s1[i];
		i ++;
	}
	j = 0;
	while (i < s1_length + s2_length)
		res[i ++] = s2[j ++];
	res[i] = '\0';
	free(s1);
	free(s2);
	return (res);
}
