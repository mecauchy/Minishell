/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:28:41 by vluo              #+#    #+#             */
/*   Updated: 2024/11/25 14:29:24 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	sizei(long n)
{
	if (n <= 9)
		return (1);
	return (1 + sizei(n / 10));
}

static char	*pitoa(long n)
{
	char	*res;
	int		si;

	if (n == 0)
		return (ft_strdup("0"));
	si = sizei(n);
	res = malloc((si + 1) * sizeof(char));
	if (res == 0)
		return (0);
	res[si --] = '\0';
	while (n > 0)
	{
		res[si --] = n % 10 + '0';
		n = n / 10;
	}
	return (res);
}

static char	*nitoa(long n)
{
	char	*res;
	int		si;

	n = -n;
	si = sizei(n);
	res = malloc((si + 2) * sizeof(char));
	if (res == 0)
		return (0);
	res[0] = '-';
	res[si + 1] = '\0';
	while (n > 0)
	{
		res[si --] = n % 10 + '0';
		n = n / 10;
	}
	return (res);
}

char	*long_itoa(long n)
{
	if (n < 0)
		return (nitoa(n));
	return (pitoa(n));
}
