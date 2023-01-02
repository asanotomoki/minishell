/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exection.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 21:06:06 by tasano            #+#    #+#             */
/*   Updated: 2023/01/02 17:43:36 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "exec.h"

t_parse_ast	*convert_cmd(t_cmd **cmd)
{
	t_parse_ast	*content;
	t_cmd		*tmpcmd;
	t_parse_ast	*tmpast;
	
	tmpcmd = *cmd;
	while (cmd)
	{
		content = execlst_new(*cmd);
		content->cmd = tmpcmd->cmd;
	}
	return (content);
}

int	exection(t_cmd *cmd)
{
	convert_cmd();
}