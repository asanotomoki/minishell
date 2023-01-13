/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:21:48 by tasano            #+#    #+#             */
/*   Updated: 2023/01/13 15:05:08 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

int *expansion(t_cmd *cmd)
{
		size_t	i;
	while (cmd)
	{
		printf("\nredirect : ");
		while (cmd)
		{
			if (cmd->redirect->type == OUTREDIRECT)
				printf (" > %s", cmd->redirect->filename);
			else if (cmd->redirect->type == OUTADDITION)
				printf (" >> %s", cmd->redirect->filename);
			else if (cmd->redirect->type == INREDIRECT)
				printf (" < %s", cmd->redirect->filename);
			else if (cmd->redirect->type == HEREDOCU)
				printf (" << %s", cmd->redirect->filename);
			cmd->redirect = cmd->redirect->next;
		}
		printf("\ncommand : [");
		while (cmd->argc!=0 && cmd->cmd[i])
		{
			printf("[%s]", cmd->cmd[i]);
			i++;
		}
		printf("]\n");
		cmd = cmd->piped_cmd;
	}
	return (cmd);
}