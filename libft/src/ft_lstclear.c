/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:53:57 by vluo              #+#    #+#             */
/*   Updated: 2024/11/18 10:48:14 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlastm1(t_list *lst)
{
	t_list	*temp;

	temp = lst;
	if (temp == 0 || temp -> next == 0)
		return (lst);
	while (temp -> next -> next != 0)
		temp = temp -> next;
	return (temp);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*dele;

	if (*lst == 0)
		return ;
	while (((*lst)-> next) != 0)
	{
		dele = ft_lstlastm1(*lst);
		ft_lstdelone(dele->next, del);
		dele ->next = 0;
	}
	ft_lstdelone(*(lst), del);
	*lst = 0;
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
// 	int *q = malloc(sizeof(int));
// 	q[0] = 0;

// 	n = ft_lstnew(k);
// 	ft_lstadd_front(&n,ft_lstnew(j));
// 	ft_lstadd_front(&n,ft_lstnew(q));
// 	ft_lstprint(n);
// 	printf("%c", '\n');
// 	ft_lstclear(&n, free);
// 	printf("%caa", '\n');
// 	ft_lstprint(n);
// }