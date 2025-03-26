/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_combo_ht.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:08:25 by vluo              #+#    #+#             */
/*   Updated: 2025/03/19 15:06:01 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	combo_ht_nb(const char *format, t_list *f, int *cpt, char c)
{
	int	total_length;
	int	precision;
	int	chr;

	total_length = ft_atoi(&format[1]);
	chr = strschr(format, ".");
	chr = go_to_width(format, chr);
	precision = flag_point_length(&format[chr], f, cpt);
	if (chr == -1)
		return (flag_ht(format, f, cpt));
	if (((char *)get_content(f, *cpt))[0] != '-')
	{
		if (total_length <= precision + 1)
		{
			ft_putchar_fd('0', 1);
			ft_putchar_fd(c, 1);
			return (flag_point(&format[chr], f, cpt) + 2);
		}
		ft_putsp(total_length - (precision + 2));
		ft_putchar_fd('0', 1);
		ft_putchar_fd(c, 1);
		flag_point(&format[chr], f, cpt);
		return (total_length);
	}
	return (combo_nb(&format[chr + 1], f, cpt, 0));
}

static int	combo_ht_dashpoint(const char *format, t_list *f, int *cpt)
{
	int		chr;
	char	c;

	c = format[strschr(format, "xX")];
	chr = strschr(&format[1], "-.123456789");
	chr = go_to_width(format, chr);
	if (format[chr + 1] == '-')
	{
		if (((char *)get_content(f, *cpt))[0] != '-'
			&& ((char *)get_content(f, *cpt))[0] != '0')
		{
			ft_putchar_fd('0', 1);
			ft_putchar_fd(c, 1);
			return (combo_dash(&format[chr + 1], f, cpt, 2) + 2);
		}
		return (combo_dash(&format[chr + 1], f, cpt, 0));
	}
	if (((char *)get_content(f, *cpt))[0] != '-'
			&& ((char *)get_content(f, *cpt))[0] != '0')
	{
		ft_putchar_fd('0', 1);
		ft_putchar_fd(c, 1);
		return (flag_point(&format[chr + 1], f, cpt) + 2);
	}
	return (flag_point(&format[chr + 1], f, cpt));
}

static int	combo_ht_zero(const char *format, t_list *f, int *cpt, char c)
{
	int		chr;
	int		total_length;
	int		precision;

	if (((char *)get_content(f, *cpt))[0] == '0')
		return (combo_zero(format, f, cpt));
	chr = go_to_width(format, strschr(&format[1], "."));
	if (chr == -1)
	{
		ft_putchar_fd('0', 1);
		ft_putchar_fd(c, 1);
		return (flag_zero(&format[chr + 1], f, cpt, 2) + 2);
	}
	total_length = ft_atoi(&format[1]);
	precision = flag_point_length(&format[chr + 1], f, cpt);
	if (total_length <= precision + 2)
	{
		ft_putchar_fd('0', 1);
		ft_putchar_fd(c, 1);
		return (flag_point(&format[chr + 1], f, cpt) + 2);
	}
	ft_putsp(total_length - (precision + 2));
	ft_putchar_fd('0', 1);
	ft_putchar_fd(c, 1);
	return (flag_point(&format[chr + 1], f, cpt) + total_length - precision);
}

int	combo_ht(const char *format, t_list *f, int *cpt)
{
	int		chr;
	char	c;

	c = format[strschr(format, "xX")];
	chr = strschr(&format[1], "-.0123456789");
	chr = go_to_width(format, chr);
	if (format[chr + 1] == '-' || format[chr + 1] == '.')
		return (combo_ht_dashpoint(format, f, cpt));
	if (format[chr + 1] == '0')
		return (combo_ht_zero(format, f, cpt, c));
	if (chr == -1)
		return (flag_ht(&format[chr + 1], f, cpt));
	return (combo_ht_nb(format, f, cpt, c));
}
