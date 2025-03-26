/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:48:42 by vluo              #+#    #+#             */
/*   Updated: 2024/11/13 15:29:16 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	return (c);
}

// #include <stdio.h>
// int	main(void)
// {
// 	printf("%c\n", ft_tolower('A'));
// 	printf("%c\n", ft_tolower('b'));
// 	printf("%c\n", ft_tolower('B'));
// 	printf("%c\n", ft_tolower('1'));
// 	printf("%c\n", ft_tolower('J'));
// }