/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 16:08:22 by vluo              #+#    #+#             */
/*   Updated: 2024/11/12 14:56:47 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i ++;
	}
}

// void f(unsigned int i, char *c)
// {
// 	*c = *c + (i - i);
//     return ;
// }

// #include <stdio.h>
// #include <stdlib.h>
// int main(void)
// {
// 	char *s;
//     s = malloc(3 * sizeof(char));
//     s[0] = 'H';
//     s[1] = 'e';
//     s[2] = '\0';
//     printf("%s\n", s);
//     ft_striteri(s, f);
//     printf("%s\n", s);
// }