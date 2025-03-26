/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_plus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:37:38 by vluo              #+#    #+#             */
/*   Updated: 2025/03/22 11:16:10 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	plus_di(int precision, t_list *f, int *cpt)
{
	char	*res;

	res = (char *) get_content(f, *cpt);
	*cpt += 1;
	if (res[0] == '-')
	{
		if (precision <= (int)ft_strlen(res))
		{
			ft_putstr_fd(res, 1);
			return (ft_strlen(res));
		}
		ft_putsp(precision - ft_strlen(res));
		ft_putstr_fd(res, 1);
		return (precision);
	}
	if (precision <= ((int)ft_strlen(res) + 1))
	{
		ft_putchar_fd('+', 1);
		ft_putstr_fd(res, 1);
		return (ft_strlen(res) + 1);
	}
	ft_putsp(precision - ft_strlen(res) - 1);
	ft_putchar_fd('+', 1);
	ft_putstr_fd(res, 1);
	return (precision);
}

int	flag_plus(const char *format, t_list *f, int *cpt)
{
	int	precision;

	precision = ft_atoi(format);
	return (plus_di(precision, f, cpt));
}
