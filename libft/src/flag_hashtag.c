/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_hashtag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:53:41 by vluo              #+#    #+#             */
/*   Updated: 2024/11/26 13:55:56 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ht_x(int precision, t_list *f, int *cpt, char c)
{
	int	length_res;

	length_res = ft_strlen((char *) get_content(f, *cpt));
	if (precision <= length_res + 2)
	{
		if (c == 'x')
			ft_putstr_fd("0x", 1);
		else
			ft_putstr_fd("0X", 1);
		ft_putstr_fd((char *) get_content(f, *cpt), 1);
		*cpt += 1;
		return (length_res + 2);
	}
	ft_putsp(precision - (length_res + 2));
	if (c == 'x')
		ft_putstr_fd("0x", 1);
	else
		ft_putstr_fd("0X", 1);
	ft_putstr_fd((char *) get_content(f, *cpt), 1);
	*cpt += 1;
	return (precision);
}

int	flag_ht(const char *format, t_list *f, int *cpt)
{
	int	precision;
	int	chr;

	precision = ft_atoi(&format[1]);
	if (ft_strncmp((char *) get_content(f, *cpt), "0", 1) == 0)
	{
		if (precision == 0)
		{
			ft_putzer(1);
			*cpt += 1;
			return (1);
		}
		ft_putsp(precision - 1);
		ft_putzer(1);
		*cpt += 1;
		return (precision);
	}
	chr = strschr(&format[1], "cspdiuxX%");
	return (ht_x(precision, f, cpt, format[chr + 1]));
}
