/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:10:26 by tasano            #+#    #+#             */
/*   Updated: 2023/01/12 11:37:08 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	put_ans(t_cmd *cmd)
{
	size_t	i;
	while (cmd)
	{
		printf("\nredirect : ");
		while (cmd->redirect)
		{
			if (cmd->redirect->type == OUTREDIRECT)
				printf (" > %s", cmd->redirect->filename);
			else if (cmd->redirect->type == INREDIRECT)
				printf (" < %s", cmd->redirect->filename);
			else if (cmd->redirect->type == OUTADDITION)
				printf (" >> %s", cmd->redirect->filename);
			else
				printf (" << %s", cmd->redirect->filename);
			cmd->redirect = cmd->redirect->next;
		}
		i = 0;
		printf("\ncommand : [");
		while (cmd->argc != 0 && cmd->cmd[i])
		{
			printf("[%s]", cmd->cmd[i]);
			i++;
		}
		printf("]\n");
		cmd = cmd->piped_cmd;
	}
	return (0);
}

int parser_test(char *input)
{
	char *cmd;

	printf ("-----[ %s ]------", input);
	cmd = strdup(input);
	put_ans(parser(lexer(cmd)));
	free(cmd);
	return (0);
}

int main()
{
	parser_test("ls -l < test1|\">|||||grep lexer\" > test2 >> test3 | wc -l | cat");
	parser_test("ls -l | wc -l | cat >> test");
	parser_test("ls");
	parser_test("ls > test > test1 << EOF << EOT < test3 > test1 < test");
	//error test
	printf("\n\n\n--------- error test ---------\n\n\n");
	parser_test("ls -l ||");
	parser_test("ls -l <<");
	return (0);	
}