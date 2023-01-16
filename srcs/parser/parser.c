/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:38:18 by tasano            #+#    #+#             */
/*   Updated: 2023/01/16 21:08:59 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int create_cmd(t_token_lst *lst, t_cmd **cmdlst, t_cmd *top, t_token_lst *tmplst)
{
	t_cmd *cmd;

	cmd = *cmdlst;
	if (parse_error(lst, top, &tmplst))
		return (1);
	if (lst->type == PIPE)
		cmd = cmd_addback(cmd, cmd_new());
	else if (lst->type == OUTREDIRECT || lst->type == OUTADDITION ||
			 lst->type == INREDIRECT || lst->type == HEREDOC)
	{
		redirection_addback(&cmd->redirect, redirection_new(lst));
		lst = lst->next;
	}
	else
		cmd->cmd = append_args(cmd->cmd, cmd->argc++, lst->token);
	return (0);
}

t_cmd *parser(t_token_lst *lst)
{
	t_cmd *cmd;
	t_cmd *tmp;
	t_token_lst *tmplst;

	tmplst = lst;
	cmd = cmd_new();
	tmp = cmd;
	while (lst)
	{
		if (parse_error(lst, tmp, &tmplst))
			break;
		if (lst->type == PIPE)
			cmd = cmd_addback(cmd, cmd_new());
		else if (lst->type == OUTREDIRECT || lst->type == OUTADDITION ||
				 lst->type == INREDIRECT || lst->type == HEREDOC)
		{
			redirection_addback(&cmd->redirect, redirection_new(lst));
			lst = lst->next;
		}
		else
			cmd->cmd = append_args(cmd->cmd, cmd->argc++, lst->token);
		lst = lst->next;
	}
	free_parser_lst(&tmplst);
	return (tmp);
}
