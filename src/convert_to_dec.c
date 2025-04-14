/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_dec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:57:10 by vluo              #+#    #+#             */
/*   Updated: 2025/04/11 18:06:25 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	octal_to_dec(char *nb)
{
	int	res;
	int	i;
	int	p;

	res = 0;
	p = 1;
	i = -1;
	while (nb[++i])
	{
		res = res + ((nb[ft_strlen(nb) - i - 1] - '0') * (p));
		p = p * 8;
	}
	return (free(nb), res);
}

int	hex_to_dec(char *nb)
{
	int	res;
	int	i;
	int	p;

	res = 0;
	p = 1;
	i = -1;
	while (nb[++i])
	{
		if (ft_isdigit(nb[ft_strlen(nb) - i - 1]) == 0)
			res = res + ((9 + ((nb[ft_strlen(nb) - i - 1] - '0') % 16)) * p);
		else
			res = res + ((nb[ft_strlen(nb) - i - 1] - '0') * (p));
		p = p * 16;
	}
	return (free(nb), res);
}
