/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:50:27 by vluo              #+#    #+#             */
/*   Updated: 2024/12/26 08:39:39 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H 

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/uio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int		len(char *str);
char	*ft_strnjoin(char *s1, char *s2, int n);
char	*get_next_line(int fd);

#endif