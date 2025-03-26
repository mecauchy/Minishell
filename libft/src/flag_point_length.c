/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_point_length.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:18:37 by vluo              #+#    #+#             */
/*   Updated: 2024/11/27 15:07:51 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	point_s_length(int precision, t_list*f, int *cpt)
{
	if (ft_strncmp((char *)get_content(f, *cpt), "(null)", 6) == 0)
	{
		if (precision < 6)
			return (0);
		return (6);
	}
	if (precision >= (int)ft_strlen((char *)get_content(f, *cpt)))
		return (ft_strlen((char *)get_content(f, *cpt)));
	return (precision);
}

static int	point_di_length(int precision, t_list *f, int *cpt)
{
	char	*res;

	res = (char *) get_content(f, *cpt);
	if (res[0] == '0' && precision == 0)
		return (0);
	if (res[0] == '-')
	{
		if (precision <= (int)ft_strlen(res) - 1)
			return (ft_strlen(res));
		return (precision + 1);
	}
	if (precision <= (int)ft_strlen(res))
		return (ft_strlen(res));
	return (precision);
}

static int	point_str_length(int precision, t_list *f, int *cpt, char flag)
{
	int	length_res;

	if ((flag == 'u' && ((char *)get_content(f, *cpt))[0] == '0'
		&& precision == 0))
		return (precision);
	length_res = ft_strlen((char *) get_content(f, *cpt));
	if (precision <= length_res)
		return (length_res);
	return (precision);
}

static int	point_x_length(int precision, t_list *f, int *cpt)
{
	char	*res;

	res = (char *) get_content(f, *cpt);
	if (precision == 0 && res[0] == '0')
		return (0);
	if (precision <= (int)ft_strlen(res))
		return ((int)ft_strlen(res));
	return (precision);
}

int	flag_point_length(const char *format, t_list *f, int *cpt)
{
	int	chr;
	int	precision;

	chr = strschr(&format[1], "cspdiuxX%");
	precision = ft_atoi(&format[1]);
	if (format[chr + 1] == 'c')
		return (1);
	if (format[chr + 1] == 's')
		return (point_s_length(precision, f, cpt));
	if (format[chr + 1] == 'd' || format[chr + 1] == 'i')
		return (point_di_length(precision, f, cpt));
	if (format[chr + 1] == 'x' || format[chr + 1] == 'X')
		return (point_x_length(precision, f, cpt));
	return (point_str_length(precision, f, cpt, format[chr + 1]));
}
