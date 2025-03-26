/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_combo_plus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:11:21 by vluo              #+#    #+#             */
/*   Updated: 2025/03/25 15:52:06 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	combo_plus_nb(const char *format, t_list *f, int *cpt)
{
	int	total_length;
	int	precision;
	int	chr;

	total_length = ft_atoi(&format[1]);
	chr = strschr(format, ".");
	chr = go_to_width(format, chr);
	precision = flag_point_length(&format[chr], f, cpt);
	if (chr == -1)
		return (flag_plus(format, f, cpt));
	if (((char *)get_content(f, *cpt))[0] != '-')
	{
		if (total_length <= precision + 1)
		{
			ft_putchar_fd('+', 1);
			return (flag_point(&format[chr], f, cpt) + 1);
		}
		ft_putsp(total_length - (precision + 1));
		ft_putchar_fd('+', 1);
		flag_point(&format[chr], f, cpt);
		return (total_length);
	}
	return (combo_nb(&format[chr + 1], f, cpt, 0));
}

int	combo_plus(const char *format, t_list *f, int *cpt)
{
	int	chr;

	chr = strschr(&format[1], "-.123456789");
	chr = go_to_width(format, chr);
	if (format[chr + 1] == '-')
	{
		if (((char *)get_content(f, *cpt))[0] != '-')
		{
			ft_putchar_fd('+', 1);
			return (combo_dash(&format[chr + 1], f, cpt, 1) + 1);
		}
		return (combo_dash(&format[chr + 1], f, cpt, 0));
	}
	if (format[chr + 1] == '.')
	{
		if (((char *)get_content(f, *cpt))[0] != '-')
		{
			ft_putchar_fd('+', 1);
			return (flag_point(&format[chr + 1], f, cpt) + 1);
		}
		return (flag_point(&format[chr + 1], f, cpt));
	}
	if (chr == -1)
		return (flag_plus(&format[chr + 1], f, cpt));
	return (combo_plus_nb(format, f, cpt));
}
