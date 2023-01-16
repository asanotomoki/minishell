/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_lstutil.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:35:13 by tasano            #+#    #+#             */
/*   Updated: 2023/01/17 02:29:21 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include "util.h"

t_redirect *redirection_new(t_token_lst *lst)
{
	t_redirect *content;

	content = (t_redirect *)malloc(sizeof(t_redirect));
	if (!content)
		return (NULL);
	content->filename = lst->next->token;
	content->type = lst->type;
	content->next = NULL;
	return (content);
}

void redirection_addback(t_redirect **lst, t_redirect *new)
{
	t_redirect *tmp;

	if (!new)
		return;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void redirect_lstfree(t_redirect **lst)
{
	t_redirect *tmp;

	tmp = *lst;
	while (tmp)
	{
		*lst = tmp->next;
		free_strval(&tmp->filename);
		
		tmp = *lst;
	}
}