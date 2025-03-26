/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:01:14 by vluo              #+#    #+#             */
/*   Updated: 2024/11/12 16:46:04 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*n;

	n = malloc(sizeof(t_list));
	if (n == 0)
		return (0);
	n -> content = content;
	n -> next = 0;
	return (n);
}

// #include <stdio.h>
// void ft_lstprint(t_list * l)
// {
//     if (!l)
//         return;
//     printf("-> %d", * (int *) (l->content));
//     ft_lstprint(l->next);
// }

// int main(void)
// {
// 	t_list *n;
// 	int *k = malloc(sizeof(int));
// 	k[0] = 1;

// 	n = ft_lstnew(k);
// 	ft_lstprint(n);
// }