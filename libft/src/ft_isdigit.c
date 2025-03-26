/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:05:31 by vluo              #+#    #+#             */
/*   Updated: 2024/11/13 14:42:01 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if ((c >= 48 && c <= 57))
		return (1);
	return (0);
}

// #include <stdio.h>
// int main(void)
// {
// 	int	n = 0;
// 	char c;

// 	while (n <= 127)
// 	{
// 		c = n;
// 		printf("%d : %c\n", ft_isdigit(n), c);
// 		n ++;
// 	}
// }