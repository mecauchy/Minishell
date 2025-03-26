/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 16:37:52 by vluo              #+#    #+#             */
/*   Updated: 2024/11/18 10:46:23 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_itoa_rec(int n, int fd)
{
	if (n == 0)
		return ;
	ft_itoa_rec(n / 10, fd);
	ft_putchar_fd(n % 10 + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		if (n == -2147483648)
			return (ft_putstr_fd("-2147483648", fd));
		n = -n;
		ft_putchar_fd('-', fd);
		return (ft_itoa_rec(n, fd));
	}
	if (n == 0)
		return (ft_putchar_fd('0', fd));
	return (ft_itoa_rec(n, fd));
}

// #include <stdio.h>
// int main(void)
// {
// 	ft_putnbr_fd(0, 1);
// 	printf("%c", '\n');
// 	ft_putnbr_fd(-2147483648, 1);
// 	printf("%c", '\n');
// 	ft_putnbr_fd(2147483647, 1);
// 	printf("%c", '\n');
// 	ft_putnbr_fd(1, 1);
// 	printf("%c", '\n');
// 	ft_putnbr_fd(10, 1);
// 	printf("%c", '\n');
// 	ft_putnbr_fd(-1, 1);
// 	printf("%c", '\n');
// 	ft_putnbr_fd(-2147483646, 1);
// 	printf("%c", '\n');
// }