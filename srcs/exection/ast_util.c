/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 21:59:00 by tasano            #+#    #+#             */
/*   Updated: 2023/01/10 23:40:31 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "exec.h"
#include <stdlib.h>

t_parse_ast *execlst_new(t_cmd *cmd)
{
	t_parse_ast *content;

	content = (t_parse_ast *)malloc(sizeof(t_parse_ast));
	if (!content)
		return (NULL);
	content->cmd = cmd->cmd;
	content->input = cmd->input;
	content->output = cmd->output;
	content->prev_pipe = NULL;
	content->next_pipe = NULL;
	return (content);
}

void execlst_addback(t_parse_ast **lst, t_parse_ast *new)
{
	t_parse_ast *tmp;

	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next_pipe)
			tmp = tmp->next_pipe;
		tmp->next_pipe = new;
		new->prev_pipe = tmp;
	}
}

t_parse_ast *execlst_addfront(t_parse_ast **lst, t_parse_ast *new)
{
	t_parse_ast *tmp;

	if (!new)
		return (*lst);
	if (!*lst)
		return (new);
	else
	{
		tmp = *lst;
		tmp->prev_pipe = new;
		new->next_pipe = tmp;
		return (new);
	}
}

void	execlst_free(t_parse_ast **cmd)
{
	t_parse_ast	*tmp;

	tmp = *cmd;
	while (tmp)
	{
		*cmd = tmp->next_pipe;
		redirect_lstfree(&tmp->input);
		redirect_lstfree(&tmp->output);
		if (tmp->cmd)
			free(tmp->cmd);
		tmp->cmd = NULL;
		tmp = NULL;
		tmp = *cmd;
	}
}