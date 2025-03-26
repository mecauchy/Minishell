/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_conversion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:21:31 by vluo              #+#    #+#             */
/*   Updated: 2024/11/27 16:37:30 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pr_char(t_list *f, int *pr_length, int *cpt)
{
	*pr_length = *pr_length + 1;
	if ((char *) get_content(f, *cpt) == 0)
	{
		ft_putchar_fd(0, 1);
		*cpt = *cpt + 1;
		return ;
	}
	ft_putstr_fd((char *)get_content(f, *cpt), 1);
	*cpt = *cpt + 1;
}

static void	pr_p(t_list *f, int *pr_length, int *cpt)
{
	if (ft_strncmp((const char *) get_content(f, *cpt), "(nil)", 5) == 0)
	{
		ft_putstr_fd((char *) get_content(f, *cpt), 1);
		*pr_length = *pr_length + 5;
		*cpt = *cpt + 1;
		return ;
	}
	ft_putstr_fd((char *)get_content(f, *cpt), 1);
	*pr_length = *pr_length + ft_strlen((char *)get_content(f, *cpt));
	*cpt = *cpt + 1;
}

static void	pr_str(t_list *f, int *pr_length, int *cpt)
{
	ft_putstr_fd((char *) get_content(f, *cpt), 1);
	*pr_length += ft_strlen((const char *)get_content(f, *cpt));
	*cpt = *cpt + 1;
}

int	pr_conversion(const char *format, t_list *f, int *pr_length, int *cpt)
{
	int		chr;
	char	*sub_format;

	chr = strschr(&format[1], "cspdiuxX%");
	if (format[chr + 1] == '%')
	{
		ft_putchar_fd('%', 1);
		*pr_length += 1;
		*cpt = *cpt + 1;
	}
	if (chr != 0 && format[chr + 1] != '%')
	{
		sub_format = ft_substr(format, 0, chr + 2);
		*pr_length += pr_flag(sub_format, f, cpt);
		free(sub_format);
		return (chr);
	}
	if (format[chr + 1] == 'c')
		pr_char(f, pr_length, cpt);
	if (format[chr + 1] == 'p')
		pr_p(f, pr_length, cpt);
	if (in_str("sdiuxX", format[chr + 1]) != -1)
		pr_str(f, pr_length, cpt);
	return (chr);
}
