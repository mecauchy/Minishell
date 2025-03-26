/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:10:53 by vluo              #+#    #+#             */
/*   Updated: 2025/01/15 11:06:12 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include "get_next_line_bonus.h"

int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
char	*ft_itoa(int n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t siz);
size_t	ft_strlcpy(char *dst, const char *src, size_t siz);
size_t	ft_strlen(const char *str);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void	ft_lstadd_back(t_list **lst, t_list *ne);
void	ft_lstadd_front(t_list **lst, t_list *ne);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);

/* FT_PRINT */

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