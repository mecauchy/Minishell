/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:14:10 by vluo              #+#    #+#             */
/*   Updated: 2024/11/25 20:13:38 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	space_di(int precision, t_list *f, int *cpt)
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
		ft_putchar_fd(' ', 1);
		ft_putstr_fd(res, 1);
		return (ft_strlen(res) + 1);
	}
	ft_putsp(precision - ft_strlen(res));
	ft_putstr_fd(res, 1);
	return (precision);
}

int	flag_space(const char *format, t_list *f, int *cpt)
{
	int	chr;
	int	precision;
	int	length_res;

	precision = ft_atoi(&format[1]);
	chr = strschr(&format[1], "cspdiuxX%");
	if (format[chr + 1] == 's')
	{
		ft_putstr_fd((char *) get_content(f, *cpt), 1);
		length_res = ft_strlen((char *) get_content(f, *cpt));
		*cpt += 1;
		if (precision <= length_res)
			return (length_res);
		ft_putsp(precision - length_res);
		return (precision);
	}
	return (space_di(precision, f, cpt));
}
