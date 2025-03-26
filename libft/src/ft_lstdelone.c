/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vluo <vluo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:39:32 by vluo              #+#    #+#             */
/*   Updated: 2024/11/14 15:13:52 by vluo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == 0 || del == 0)
		return ;
	del(lst -> content);
	free(lst);
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
// 	n = ft_lstnew(k);
// 	ft_lstprint(n);
// 	ft_lstdelone(n, free);
// }