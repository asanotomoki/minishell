/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lstutil.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:35:13 by tasano            #+#    #+#             */
/*   Updated: 2023/01/20 03:17:04 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include "util.h"
#include "libft.h"

t_cmd	*cmd_new(void)
{
	t_cmd	*content;

	content = (t_cmd *)malloc(sizeof(t_cmd));
	if (!content)
		return (NULL);
	content->cmd = NULL;
	content->redirect = NULL;
	content->piped_cmd = NULL;
	content->argc = 0;
	content->type = 0;
	return (content);
}

t_cmd	*cmd_addback(t_cmd *lst, t_cmd *new)
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

void	cmd_lstfree(t_cmd **cmd)
{
	t_cmd	*tmp;

	tmp = *cmd;
	while (tmp)
	{
		*cmd = tmp->piped_cmd;
		redirect_lstfree(&tmp->redirect);
		if (tmp->cmd)
			free_args(&tmp->cmd);
		tmp->piped_cmd = NULL;
		tmp->argc = 0;
		free(tmp);
		tmp = NULL;
		tmp = *cmd;
	}
}
