/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_dash_length.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:45:05 by vluo              #+#    #+#             */
/*   Updated: 2024/11/26 17:08:24 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	dash_p_length(int precision, t_list *f, int *cpt)
{
	int	length_res;

	length_res = ft_strlen((char *) get_content(f, *cpt));
	if (precision <= length_res)
		return (length_res);
	return (precision);
}

static int	dash_str_length(int precision, t_list *f, int *cpt)
{
	int	length_res;

	length_res = ft_strlen((char *) get_content(f, *cpt));
	if (length_res == 0)
		return (precision);
	if (precision <= length_res)
		return (length_res);
	return (precision);
}

int	flag_dash_length(const char *format, t_list *f, int *cpt, int otherflag)
{
	int	chr;
	int	precision;

	chr = strschr(&format[1], "cspdiuxX%");
	precision = ft_atoi(&format[1]) - otherflag;
	if (format[chr + 1] == 'c')
	{
		if (precision <= 0)
			return (1);
		return (precision);
	}
	if (format[chr + 1] == 'p')
		return (dash_p_length(precision, f, cpt));
	return (dash_str_length(precision, f, cpt));
}
