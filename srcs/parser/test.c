/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:10:26 by tasano            #+#    #+#             */
/*   Updated: 2022/12/28 17:46:12 by tasano           ###   ########.fr       */
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
		printf("\noutput : ");
		while (cmd->output)
		{
			if (cmd->output->type == OUTREDIRECT)
				printf (" > %s", cmd->output->filename);
			else
				printf (" >> %s", cmd->output->filename);
			cmd->output = cmd->output->next;
		}
		printf("\ninput : ");
		while (cmd->input)
		{
			if (cmd->input->type == INREDIRECT)
				printf (" < %s", cmd->input->filename);
			else
				printf (" << %s", cmd->input->filename);
			cmd->input = cmd->input->next;
		}
		i = 0;
		printf("\ncommand : [");
		while (cmd->argc!=0 && cmd->cmd[i])
		{
			printf("[%s]", cmd->cmd[i]);
			i++;
		}
		printf("]\n");
		cmd = cmd->piped_cmd;
	}
	return (0);
}

int main()
{
	printf("\n-----test1------\n");
	char *input = strdup("ls -l < test1|\">|||||grep lexer\" > test2 >> test3 | wc -l | cat");
	put_ans(parser(lexer(input)));
	free (input);
	printf("\n-----test2------\n");
	input = strdup("ls -l | wc -l | cat >> test");
	put_ans(parser(lexer(input)));
	free(input);
	printf("\n-----test3------\n");
	input = strdup("ls");
	put_ans(parser(lexer(input)));
	free(input);
	//error test
	printf("\n-----test4------\n");
	input = strdup("ls -l ||");
	put_ans(parser(lexer(input)));
	free(input);
	printf("\n-----test5------\n");
	input = strdup("ls -l <<");
	put_ans(parser(lexer(input)));
	printf("\n-----test6------\n");
	input = strdup("ls -l << <");
	put_ans(parser(lexer(input)));
	free(input);
	return (0);	
}