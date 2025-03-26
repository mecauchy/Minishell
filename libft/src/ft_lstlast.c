/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:30:55 by vluo              #+#    #+#             */
/*   Updated: 2024/11/18 18:02:57 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == 0)
		return (lst);
	while (lst -> next != 0)
		lst = lst -> next;
	return (lst);
}

// t_list	*ft_lstnew(void *content)
// {
// 	t_list	*n;

// 	n = malloc(sizeof(t_list));
// 	if (n == 0)
// 		return (0);
// 	n -> content = content;
// 	n -> next = 0;
// 	return (n);
// }

// void	ft_lstadd_front(t_list **lst, t_list *new)
// {
// 	new -> next = *lst;
// 	*lst = new;
// }

// #include <stdio.h>
// void ft_lstprint(t_list * l)
// {
//     if (!l)
//         return;
//     printf("-> %d", * (int *) (l->content));
//     ft_lstprint(l->next);
// }

// #include <stdio.h>
// int main(void)
// {
// 	t_list *n;
// 	int *k = malloc(sizeof(int));
// 	k[0] = 10;
// 	int *j = malloc(sizeof(int));
// 	j[0] = 1;

// 	n = ft_lstnew(k);
// 	ft_lstadd_front(&n,ft_lstnew(j));
// 	ft_lstprint(ft_lstlast(n));
// }
