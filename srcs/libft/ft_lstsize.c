/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 17:51:03 by hiroaki           #+#    #+#             */
/*   Updated: 2022/03/10 21:55:39 by hmakino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

//#include <stdio.h>
//
//int main(void)
//{
//	t_list	*node_tanaka;
//	t_list	*node_yamada;
//	t_list	*node_makino;
//
//	node_tanaka = ft_lstnew("tanaka");
//	node_yamada = ft_lstnew("yamada");
//	node_makino = ft_lstnew("makino");
//	node_tanaka->next = node_yamada;
//	node_yamada->next = node_makino;
//	printf("\nlstsize : %d\n", ft_lstsize(node_tanaka));
//}
