/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:39:36 by vluo              #+#    #+#             */
/*   Updated: 2025/01/15 11:13:40 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	go_to_width(const char *format, int chr)
{
	int	i;

	i = chr;
	if (ft_isdigit(format[chr + 1]))
	{
		if (format[chr + 1] == '0')
		{
			while (format[i + 1] == '0')
				i ++;
			return (i - 1);
		}
		return (i);
	}
	while (format[i + 1] == format[chr + 1])
		i ++;
	return (i - 1);
}

int	pr_flag(const char *format, t_list *f, int *cpt)
{
	int	chr;

	chr = strschr(&format[1], " +#-.0123456789");
	chr = go_to_width(format, chr);
	if (format[chr + 1] == '-')
		return (combo_dash(&format[chr + 1], f, cpt, 0));
	if (format[chr + 1] == '0')
		return (combo_zero(&format[chr + 1], f, cpt));
	if (format[chr + 1] == '.')
		return (flag_point(&format[chr + 1], f, cpt));
	if (format[chr + 1] == '#')
		return (combo_ht(&format[chr + 1], f, cpt));
	if (format[chr + 1] == ' ')
		return (combo_space(&format[chr + 1], f, cpt));
	if (format[chr + 1] == '+')
		return (combo_plus(&format[chr + 1], f, cpt));
	return (combo_nb(&format[chr + 1], f, cpt, 0));
}
