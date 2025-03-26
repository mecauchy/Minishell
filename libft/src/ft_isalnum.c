/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:07:36 by vluo              #+#    #+#             */
/*   Updated: 2024/11/18 11:19:42 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

// #include <stdio.h>
// int main(void)
// {
// 	int	n = 0;
// 	char c;

// 	while (n <= 127)
// 	{
// 		c = n;
// 		printf("%d : %c\n", ft_isalnum(n), c);
// 		n ++;
// 	}
// }