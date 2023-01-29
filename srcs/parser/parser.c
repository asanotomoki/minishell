/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:38:18 by tasano            #+#    #+#             */
/*   Updated: 2023/01/29 23:56:03 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "util.h"

static t_token_lst	*set_cmdval(t_token_lst *lst, t_cmd *cmd)
{
	if (lst->type == OUTREDIRECT || lst->type == OUTADDITION || \
		lst->type == INREDIRECT || lst->type == HEREDOCU)
	{
		redirection_addback(&cmd->redirect, redirection_new(lst));
		lst = lst->next;
	}
	else
		cmd->cmd = append_args(cmd->cmd, cmd->argc++, lst->token);
	return (lst);
}

static t_cmd	*pipe_error(t_token_lst **lst)
{
	put_parse_error("|");
	token_lstfree(lst);
	return (NULL);
}

t_cmd	*parser(t_token_lst *lst)
{
	t_cmd		*cmd;
	t_cmd		*top;
	t_token_lst	*tmplst;

	tmplst = lst;
	if (lst->type == PIPE)
		return (pipe_error(&tmplst));
	cmd = cmd_new();
	top = cmd;
	while (lst)
	{
		if (parse_error(lst, &top, &tmplst))
			return (NULL);
		if (lst->type == PIPE)
			cmd = cmd_addback(cmd, cmd_new());
		else
			lst = set_cmdval(lst, cmd);
		lst = lst->next;
	}
	token_lstfree(&tmplst);
	return (top);
}
