/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:38:18 by tasano            #+#    #+#             */
/*   Updated: 2023/01/12 11:28:19 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd *parser(t_token_lst *lst)
{
	t_cmd *cmd;
	t_cmd *tmp;
	t_token_lst *tmplst;

	cmd = cmd_new();
	tmp = cmd;
	tmplst = lst;
	while (lst)
	{
		if (parse_error(lst, tmp, &tmplst))
			break ;
		if (lst->type == PIPE)
			cmd = cmd_addback(cmd, cmd_new());
		else if (lst->type == OUTREDIRECT || lst->type == OUTADDITION || lst->type == INREDIRECT || lst->type == HEREDOCU)
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