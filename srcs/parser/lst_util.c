/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 20:14:22 by tasano            #+#    #+#             */
/*   Updated: 2022/12/27 22:25:12 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include <stdlib.h>

t_cmd *cmd_new()
{
	t_cmd *content;

	content = (t_cmd *)malloc(sizeof(t_cmd));
	if (!content)
		return (NULL);
	content->cmd = NULL;
	content->input = NULL;
	content->output = NULL;
	content->piped_cmd = NULL;
	content->argc = 0;
	return (content);
}

t_redirection *redirection_new(t_token_lst *lst)
{
	t_redirection *content;

	content = (t_redirection *)malloc(sizeof(t_redirection));
	if (!content)
		return (NULL);
	content->filename = lst->next->token;
	content->type = lst->type;
	content->expnad_type = lst->next->type;
	content->next = NULL;
	return (content);
}

t_cmd *cmd_addback(t_cmd *lst, t_cmd *new)
{
	if (!new)
		return (NULL);
	if (!lst)
		return (new);
	else
	{
		while (lst->piped_cmd)
			lst = lst->piped_cmd;
		lst->piped_cmd = new;
		return (lst->piped_cmd);
	}
}

void redirection_addback(t_redirection **lst, t_redirection *new)
{
	t_redirection *tmp;

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