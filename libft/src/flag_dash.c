/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_dash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:45:05 by vluo              #+#    #+#             */
/*   Updated: 2024/11/26 17:12:07 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	dash_c(int precision, t_list *f, int *cpt)
{
	if ((char *) get_content(f, *cpt) == 0)
		ft_putchar_fd(0, 1);
	else
		ft_putstr_fd((char *)get_content(f, *cpt), 1);
	*cpt = *cpt + 1;
	ft_putsp(precision - 1);
	if (precision <= 0)
		return (1);
	return (precision);
}

static int	dash_p(int precision, t_list *f, int *cpt)
{
	int	length_res;

	length_res = ft_strlen((char *) get_content(f, *cpt));
	if (ft_strncmp((const char *) get_content(f, *cpt), "(nil)", 5) == 0)
	{
		ft_putstr_fd((char *) get_content(f, *cpt), 1);
		ft_putsp(precision - length_res);
		*cpt += 1;
		if (precision <= 5)
			return (5);
		return (precision);
	}
	ft_putstr_fd((char *) get_content(f, *cpt), 1);
	ft_putsp(precision - length_res);
	*cpt += 1;
	if (precision <= length_res)
		return (length_res);
	return (precision);
}

static int	dash_str(int precision, t_list *f, int *cpt)
{
	int	length_res;

	length_res = ft_strlen((char *) get_content(f, *cpt));
	if (length_res == 0)
	{
		ft_putstr_fd((char *) get_content(f, *cpt), 1);
		ft_putsp(precision - length_res);
		*cpt += 1;
		return (precision);
	}
	if (precision <= length_res)
	{
		ft_putstr_fd((char *) get_content(f, *cpt), 1);
		*cpt = *cpt + 1;
		return (length_res);
	}
	ft_putstr_fd((char *) get_content(f, *cpt), 1);
	ft_putsp(precision - length_res);
	*cpt = *cpt + 1;
	return (precision);
}

int	flag_dash(const char *format, t_list *f, int *cpt, int otherflag)
{
	int	chr;
	int	precision;

	chr = strschr(&format[1], "cspdiuxX%");
	precision = ft_atoi(&format[1]) - otherflag;
	if (format[chr + 1] == 'c')
		return (dash_c(precision, f, cpt));
	if (format[chr + 1] == 'p')
		return (dash_p(precision, f, cpt));
	return (dash_str(precision, f, cpt));
}
