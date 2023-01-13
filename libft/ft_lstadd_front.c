/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:48:37 by hiroaki           #+#    #+#             */
/*   Updated: 2022/06/21 18:48:54 by hmakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		new->next = NULL;
	}
	else
	{
		new->next = *lst;
		*lst = new;
	}
}

//#include <stdio.h>
//
//int main(void)
//{
//	t_list	*node_first;
//	t_list	*node_second;
//	t_list	*node_third;
//
//	node_first = ft_lstnew("1st");
//	node_second = ft_lstnew("2nd");
//	node_third = ft_lstnew("3rd");
//	node_second->next = node_third;
//
//	ft_lstadd_front(&node_second, node_first);
//	while (node_first)
//	{
//		printf("\nnode->content : %s\n", (char *)node_first->content);
//		node_first = node_first->next;
//	}
//	return (0);
//}
