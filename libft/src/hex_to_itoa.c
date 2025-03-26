/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_to_itoa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:11:55 by vluo              #+#    #+#             */
/*   Updated: 2024/11/25 14:30:57 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	hex_to_itoa_length(unsigned long int nb)
{
	if (nb == 0)
		return (1);
	return (1 + hex_to_itoa_length(nb / 16));
}

char	*ft_hex_itoa(unsigned long int nb, char c)
{
	char	*res;
	char	*l_or_u;
	size_t	si;

	if (nb == 0)
		return (ft_strdup("0"));
	si = hex_to_itoa_length(nb) - 1;
	res = malloc((si + 1) * sizeof(char));
	if (res == 0)
		return (0);
	res[si --] = '\0';
	if (c == 'x')
		l_or_u = ft_strdup("0123456789abcdef");
	else
		l_or_u = ft_strdup("0123456789ABCDEF");
	while (nb > 0)
	{
		res[si --] = l_or_u[nb % 16];
		nb = nb / 16;
	}
	free(l_or_u);
	return (res);
}
