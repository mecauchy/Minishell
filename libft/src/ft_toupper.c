/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:45:59 by vluo              #+#    #+#             */
/*   Updated: 2024/11/13 15:30:20 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	return (c);
}

// #include <stdio.h>
// int	main(void)
// {
// 	printf("%c\n", ft_toupper('A'));
// 	printf("%c\n", ft_toupper('b'));
// 	printf("%c\n", ft_toupper('B'));
// 	printf("%c\n", ft_toupper('1'));
// 	printf("%c\n", ft_toupper('j'));
// }