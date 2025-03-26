/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_zero.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:44:33 by vluo              #+#    #+#             */
/*   Updated: 2024/11/26 17:53:52 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	zero_di(int precision, t_list *f, int *cpt)
{
	char	*res;
	int		res_length;

	res = (char *) get_content(f, *cpt);
	*cpt += 1;
	res_length = ft_strlen(res);
	if (precision <= res_length)
	{
		ft_putstr_fd(res, 1);
		return (res_length);
	}
	if (res[0] == '-')
	{
		ft_putchar_fd('-', 1);
		ft_putzer(precision - res_length);
		ft_putstr_fd(&res[1], 1);
		return (precision);
	}
	ft_putzer(precision - res_length);
	ft_putstr_fd(res, 1);
	return (precision);
}

static int	zero_str(int precision, t_list *f, int *cpt)
{
	int	length_res;

	length_res = ft_strlen((char *) get_content(f, *cpt));
	if (precision <= length_res)
	{
		ft_putstr_fd((char *) get_content(f, *cpt), 1);
		*cpt += 1;
		return (length_res);
	}
	ft_putzer(precision - length_res);
	ft_putstr_fd((char *) get_content(f, *cpt), 1);
	*cpt += 1;
	return (precision);
}

int	flag_zero(const char *format, t_list *f, int *cpt, int otherflag)
{
	int	chr;
	int	precision;

	chr = strschr(&format[1], "cspdiuxX%");
	precision = ft_atoi(&format[1]) - otherflag;
	if (format[chr + 1] == 'd' || format[chr + 1] == 'i')
		return (zero_di(precision, f, cpt));
	return (zero_str(precision, f, cpt));
}
