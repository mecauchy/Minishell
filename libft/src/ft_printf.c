/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:39:52 by vluo              #+#    #+#             */
/*   Updated: 2024/12/05 14:00:02 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pr_format(const char *format, t_list *f, int *pr_length)
{
	int	i;
	int	cpt;

	i = 0;
	cpt = 1;
	while (i < (int)ft_strlen(format))
	{
		if (format[i] == '%')
			i += pr_conversion(&format[i], f, pr_length, &cpt) + 2;
		else
		{
			ft_putchar_fd(format[i ++], 1);
			*pr_length += 1;
		}
	}
	return ;
}

int	ft_printf(const char *format, ...)
{
	t_list	*f;
	va_list	args;
	int		pr_length;

	if (format == 0)
		return (-1);
	va_start(args, format);
	pr_length = 0;
	f = ft_format(format, args);
	pr_format(format, f, &pr_length);
	ft_lstclear(&f, free);
	va_end(args);
	return (pr_length);
}
