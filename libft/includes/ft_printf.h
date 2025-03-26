/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:38:22 by vluo              #+#    #+#             */
/*   Updated: 2024/12/21 19:06:08 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define PTRNULL "(nil)"

# include "libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

void	ft_putsp(int precision);
void	ft_putzer(int precision);
char	*char_str(char c);
char	*add_x(char *str, char c);
char	*ft_hex_itoa(unsigned long int nb, char c);
char	*long_itoa(long n);
t_list	*ft_format(const char *format, va_list args);
void	*get_content(t_list *f, int ind);
int		strschr(const char *s, char *set);
int		in_str(char *str, char c);
char	*ft_strcat(char *s1, char *s2);
int		pr_conversion(const char *format, t_list *f, int *pr_length, int *cpt);
int		ft_printf(const char *format, ...);

/* bonus functions */
int		go_to_width(const char *format, int chr);
int		pr_flag(const char *format, t_list *f, int *cpt);
int		flag_dash(const char *format, t_list *f, int *cpt, int otherflag);
int		flag_dash_length(const char *format,
			t_list *f, int *cpt, int otherflag);
int		flag_point(const char *format, t_list *f, int *cpt);
int		flag_point_length(const char *format, t_list *f, int *cpt);
int		flag_zero(const char *format, t_list *f, int *cpt, int otherflag);
int		flag_zero_length(const char *format,
			t_list *f, int *cpt, int otherflag);
int		flag_nb(const char *format, t_list *f, int *cpt, int otherflag);
int		flag_ht(const char *format, t_list *f, int *cpt);
int		flag_space(const char *format, t_list *f, int *cpt);
int		flag_plus(const char *format, t_list *f, int *cpt);
int		combo_dash(const char *format, t_list *f, int *cpt, int otherflag);
int		combo_zero(const char *format, t_list *f, int *cpt);
int		combo_nb(const char *format, t_list *f, int *cpt, int otherflag);
int		combo_ht(const char *format, t_list *f, int *cpt);
int		combo_plus(const char *format, t_list *f, int *cpt);
int		combo_space(const char *format, t_list *f, int *cpt);

#endif