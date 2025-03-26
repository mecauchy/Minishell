/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_nb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:14:12 by vluo              #+#    #+#             */
/*   Updated: 2024/11/27 15:49:41 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	nb_c(int precision, t_list *f, int *cpt)
{
	if ((char *) get_content(f, *cpt) == 0)
	{
		ft_putsp(precision - 1);
		ft_putchar_fd(0, 1);
		*cpt += 1;
		return (precision);
	}
	ft_putsp(precision - 1);
	ft_putstr_fd((char *)get_content(f, *cpt), 1);
	*cpt = *cpt + 1;
	return (precision);
}

static int	nb_str(int precision, t_list *f, int *cpt)
{
	int	length_res;

	length_res = ft_strlen((char *) get_content(f, *cpt));
	if (precision <= length_res)
	{
		ft_putstr_fd((char *) get_content(f, *cpt), 1);
		*cpt += 1;
		return (length_res);
	}
	ft_putsp(precision - length_res);
	ft_putstr_fd((char *) get_content(f, *cpt), 1);
	*cpt += 1;
	return (precision);
}

int	flag_nb(const char *format, t_list *f, int *cpt, int otherflag)
{
	int	chr;
	int	precision;

	chr = strschr(&format[1], "cspdiuxX%");
	precision = ft_atoi(format) - otherflag;
	if (format[chr + 1] == 'c')
		return (nb_c(precision, f, cpt));
	return (nb_str(precision, f, cpt));
}
