/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:39:41 by vluo              #+#    #+#             */
/*   Updated: 2024/11/25 14:29:43 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*checknulp(unsigned long long p)
{
	char	*hex;
	char	*res;

	if (p == 0)
		return (ft_strdup(PTRNULL));
	hex = ft_hex_itoa(p, 'x');
	if (hex == 0)
		return (0);
	res = add_x(hex, 'x');
	return (res);
}

static void	f_add(char c, t_list *f, va_list args)
{
	char	*s;

	if (c == 'c')
		ft_lstadd_back(&f, ft_lstnew(char_str((char)(va_arg(args, int)))));
	if (c == 's')
	{
		s = va_arg(args, char *);
		if (s == 0)
			ft_lstadd_back(&f, ft_lstnew(ft_strdup("(null)")));
		else
			ft_lstadd_back(&f, ft_lstnew(ft_strdup(s)));
	}
	if (c == 'p')
		ft_lstadd_back(&f, ft_lstnew(
				checknulp(va_arg(args, unsigned long int))));
	if (c == 'd' || c == 'i')
		ft_lstadd_back(&f, ft_lstnew(ft_itoa(va_arg(args, int))));
	if (c == 'u')
		ft_lstadd_back(&f, ft_lstnew(
				long_itoa((long) va_arg(args, unsigned int))));
	if (c == 'x' || c == 'X')
		ft_lstadd_back(&f, ft_lstnew(
				ft_hex_itoa(va_arg(args, unsigned int), c)));
	if (c == '%')
		ft_lstadd_back(&f, ft_lstnew(char_str(c)));
}

t_list	*ft_format(const char *format, va_list args)
{
	t_list	*f;
	int		i;
	int		chr;

	f = ft_lstnew(0);
	i = 0;
	while (i < (int) ft_strlen(format))
	{
		if (format[i] == '%')
		{
			chr = strschr(&format[i + 1], "cspdiuxX%");
			if (chr == -1)
				return (f);
			f_add(format[chr + i + 1], f, args);
			i += chr + 1;
		}
		i ++;
	}
	return (f);
}

void	*get_content(t_list *f, int ind)
{
	if (f == 0)
		return (0);
	f = f -> next;
	while (ind > 1)
	{
		f = f -> next;
		ind --;
	}
	return (f -> content);
}

int	in_str(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i ++;
	}
	return (-1);
}
