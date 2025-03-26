/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:35:00 by vluo              #+#    #+#             */
/*   Updated: 2024/11/18 17:58:42 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	sizei(int n)
{
	if (n <= 9)
		return (1);
	return (1 + sizei(n / 10));
}

static char	*pitoa(int n)
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

static char	*nitoa(int n)
{
	char	*res;
	int		si;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
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

char	*ft_itoa(int n)
{
	if (n < 0)
		return (nitoa(n));
	return (pitoa(n));
}

// #include <stdio.h>
// int main(void)
// {
// 	printf("%s\n",ft_itoa(2147483647));
// 	printf("%s\n",ft_itoa(-2147483648));
// 	printf("%s\n",ft_itoa(0));
// 	printf("%s\n",ft_itoa(-1));
// 	printf("%s\n",ft_itoa(1));
// 	printf("%s\n",ft_itoa(-2147483647));
// 	printf("%s\n",ft_itoa(10));
// 	printf("%s\n",ft_itoa(100));
// }
