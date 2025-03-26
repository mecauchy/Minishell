/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_zero_length.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:44:33 by vluo              #+#    #+#             */
/*   Updated: 2024/11/26 18:18:22 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	zero_di_length(int precision, t_list *f, int *cpt)
{
	char	*res;
	int		res_length;

	res = (char *) get_content(f, *cpt);
	res_length = ft_strlen(res);
	if (precision <= res_length)
		return (res_length);
	if (res[0] == '-')
		return (precision);
	return (precision);
}

static int	zero_str_length(int precision, t_list *f, int *cpt)
{
	int	length_res;

	length_res = ft_strlen((char *) get_content(f, *cpt));
	if (precision <= length_res)
		return (length_res);
	return (precision);
}

int	flag_zero_length(const char *format, t_list *f, int *cpt, int otherflag)
{
	int	chr;
	int	precision;

	chr = strschr(&format[1], "cspdiuxX%");
	precision = ft_atoi(&format[1]) - otherflag;
	if (format[chr + 1] == 'd' || format[chr + 1] == 'i')
		return (zero_di_length(precision, f, cpt));
	return (zero_str_length(precision, f, cpt));
}
