/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:54:03 by vluo              #+#    #+#             */
/*   Updated: 2024/11/18 15:50:30 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	d;

	d = c % 256;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == d)
			return ((char *) &s[i]);
		s ++;
	}
	if (c == '\0')
		return ((char *) s);
	return (0);
}
// #include <stdio.h>
// int main(int argc, char **argv)
// {
// 	printf("%s", ft_strchr(argv[1], argv[2][0]));
// 	return (argc - argc);
// }