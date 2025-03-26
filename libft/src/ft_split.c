/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:47:30 by vluo              #+#    #+#             */
/*   Updated: 2025/03/21 18:32:55 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	len_spli(char const *s, char c, int b)
{
	int	len;
	int	i;

	i = 0;
	if (b == 0)
	{
		while (s[i])
			i ++;
		return (i);
	}
	len = 0;
	while (s[i] && s[i] == c)
		i ++;
	while (i < len_spli(s, 'o', 0) - 1)
	{
		if (s[i] == c && s[i + 1] != c)
			len ++;
		i ++;
	}
	return (len + 1);
}

static char	**sp_vide(void)
{
	char	**sp_vide;

	sp_vide = malloc(1 * sizeof(char *));
	if (sp_vide == 0)
		return (0);
	sp_vide[0] = 0;
	return (sp_vide);
}

static char	**check_alloc(char **sp)
{
	int	i;

	i = 0;
	while (sp[i])
	{
		if (sp[i] == 0)
		{
			i = 0;
			while (sp[i])
				free(sp[i ++]);
			free(sp);
			return (0);
		}
		i ++;
	}
	return (sp);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		start;
	int		j;
	char	**sp;

	if (s[0] == '\0')
		return (sp_vide());
	sp = malloc((len_spli(s, c, 1) + 1) * sizeof(char *));
	if (sp == 0)
		return (0);
	start = 0;
	i = 0;
	j = 0;
	while (i < len_spli(s, 'o', 0))
	{
		while (s[i] && s[i] != c)
			i ++;
		if (start != i)
			sp[j ++] = ft_substr(s, start, i - start);
		start = ++ i;
	}
	sp[j] = 0;
	return (check_alloc(sp));
}

// #include <stdio.h>
// int main(void)
// {
// 	char *s = "Hello World";
// 	char c = 'l';
// 	char **sp = ft_split(s, c);
// 	printf("%d\n", len_spli(s, c, 1));
// 	int i = 0;
// 	while (sp[i] != 0)
// 	{
// 		printf("%s\n", sp[i]);
// 		free(sp[i]);
// 		i ++;
// 	}
// 	free(sp);
// }
