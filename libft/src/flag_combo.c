/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_combo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:47:32 by vluo              #+#    #+#             */
/*   Updated: 2024/11/27 15:47:03 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	combo_dash(const char *format, t_list *f, int *cpt, int otherflag)
{
	int	total_length;
	int	length_point;
	int	chr;

	total_length = ft_atoi(&format[1]) - otherflag;
	chr = strschr(format, ".");
	chr = go_to_width(format, chr);
	if (chr == -1)
		return (flag_dash(format, f, cpt, otherflag));
	length_point = flag_point_length(&format[chr], f, cpt);
	if (total_length <= length_point)
		return (flag_point(&format[chr], f, cpt));
	flag_point(&format[chr], f, cpt);
	ft_putsp(total_length - length_point);
	return (total_length);
}

int	combo_zero(const char *format, t_list *f, int *cpt)
{
	int	chr;

	chr = strschr(&format[1], ".");
	chr = go_to_width(format, chr);
	if (chr == -1)
		return (flag_zero(format, f, cpt, 0));
	return (combo_nb(format, f, cpt, 0));
}

int	combo_nb(const char *format, t_list *f, int *cpt, int otherflag)
{
	int	total_length;
	int	length_point;
	int	chr;

	total_length = ft_atoi(format) - otherflag;
	chr = strschr(format, ".");
	chr = go_to_width(format, chr);
	if (chr == -1)
		return (flag_nb(format, f, cpt, otherflag));
	length_point = flag_point_length(&format[chr], f, cpt);
	if (total_length <= length_point)
		return (flag_point(&format[chr], f, cpt));
	ft_putsp(total_length - length_point);
	return (flag_point(&format[chr], f, cpt) + total_length - length_point);
}
