/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_combo_space.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:12:15 by vluo              #+#    #+#             */
/*   Updated: 2024/11/27 15:20:50 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	combo_sp_nb(const char *format, t_list *f, int *cpt, int chr)
{
	if (((char *)get_content(f, *cpt))[0] != '-')
	{
		ft_putsp(1);
		return (combo_nb(&format[chr + 1], f, cpt, 1) + 1);
	}
	return (combo_nb(&format[chr + 1], f, cpt, 0));
}

int	combo_space(const char *format, t_list *f, int *cpt)
{
	int	chr;

	chr = strschr(&format[1], "-.123456789");
	chr = go_to_width(format, chr);
	if (format[chr + 1] == '-')
	{
		if (((char *)get_content(f, *cpt))[0] != '-')
		{
			ft_putsp(1);
			return (combo_dash(&format[chr + 1], f, cpt, 1) + 1);
		}
		return (combo_dash(&format[chr + 1], f, cpt, 0));
	}
	if (format[chr + 1] == '.')
	{
		if (((char *)get_content(f, *cpt))[0] != '-')
		{
			ft_putsp(1);
			return (flag_point(&format[chr + 1], f, cpt) + 1);
		}
		return (flag_point(&format[chr + 1], f, cpt));
	}
	if (chr == -1)
		return (flag_space(&format[chr + 1], f, cpt));
	return (combo_sp_nb(format, f, cpt, chr));
}
