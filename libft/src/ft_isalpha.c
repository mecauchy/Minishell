/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:00:32 by vluo              #+#    #+#             */
/*   Updated: 2024/11/13 14:40:27 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

// #include <stdio.h>
// int main(void)
// {
// 	int	n = 0;
// 	char c;

// 	while (n < 127)
// 	{
// 		c = n;
// 		printf("%d : %c\n", ft_isalpha(n), c);
// 		n ++;
// 	}
// }