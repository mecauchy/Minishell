/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:19:37 by vluo              #+#    #+#             */
/*   Updated: 2024/11/18 10:51:13 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ls_map;
	t_list	*n;
	t_list	*ls;

	ls = lst;
	if (ls != 0)
	{
		ls_map = ft_lstnew(f(lst -> content));
		if (ls_map == 0)
			return (0);
		ls = ls -> next;
		while (ls != 0)
		{
			n = ft_lstnew(f(ls -> content));
			if (n == 0)
			{
				ft_lstclear(&ls_map, del);
				return (0);
			}
			ft_lstadd_back(&ls_map, n);
			ls = ls -> next;
		}
		return (ls_map);
	}
	return (0);
}

// #include <stdio.h>
// void ft_lstprint(t_list * l)
// {
//     if (!l)
//         return;
//     printf("-> %d", * (int *) (l->content));
//     ft_lstprint(l->next);
// }
// void *same(void *c)
// {
// 	int *i;
// 	int *d;
// 	d = malloc(sizeof(int));
// 	i = c;
// 	*d = *i;
// 	return (d);
// }

// #include <stdio.h>
// int main(void)
// {
// 	t_list *n;
// 	t_list *p;
// 	int *k = malloc(sizeof(int));
// 	k[0] = 10;
// 	int *j = malloc(sizeof(int));
// 	j[0] = 1;

// 	n = ft_lstnew(k);
// 	ft_lstadd_front(&n,ft_lstnew(j));
// 	p = ft_lstmap(n, same, free);
// 	ft_lstprint(n);
// 	printf("%c", '\n');
// 	ft_lstprint(p);
// 	printf("%c", '\n');
// 	ft_lstclear(&p, free);
// 	ft_lstclear(&n, free);
// }
