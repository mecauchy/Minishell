/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putcharstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:59:15 by vluo              #+#    #+#             */
/*   Updated: 2024/11/25 15:32:53 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putsp(int precision)
{
	int	i;

	if (precision < 0)
		return ;
	i = 0;
	while (i < precision)
	{
		ft_putchar_fd(' ', 1);
		i ++;
	}
	return ;
}

void	ft_putzer(int precision)
{
	int	i;

	if (precision < 0)
		return ;
	i = 0;
	while (i < precision)
	{
		ft_putchar_fd('0', 1);
		i ++;
	}
	return ;
}

char	*char_str(char c)
{
	char	*res;

	if (c == 0)
		return (0);
	res = malloc(sizeof(char) * 2);
	if (res == 0)
		return (0);
	res[0] = c;
	res[1] = '\0';
	return (res);
}

char	*add_x(char *str, char c)
{
	char	*res;

	if (c == 'x')
		res = ft_strcat(ft_strdup("0x"), str);
	else
		res = ft_strcat(ft_strdup("0X"), str);
	return (res);
}
