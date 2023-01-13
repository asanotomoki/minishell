/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:19:06 by tasano            #+#    #+#             */
/*   Updated: 2023/01/14 02:16:18 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "parser.h"
#include "lexer.h"

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
			else if (cmd->redirect->type == OUTADDITION)
				printf (" >> %s", cmd->redirect->filename);
			else if (cmd->redirect->type == INREDIRECT)
				printf (" < %s", cmd->redirect->filename);
			else if (cmd->redirect->type == HEREDOCU)
				printf (" << %s", cmd->redirect->filename);
			cmd->redirect = cmd->redirect->next;
		}
		printf("\ncommand : [");
		i = 0;
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

int put_test(char *input)
{
	t_cmd *cmd;

	printf("\n------- [ %s ] -------\n", input);
	cmd = parser(lexer(input));
	expansion(cmd);
	return (put_ans(cmd));
}

int main()
{	
	put_test("ls $USER");
	put_test("ls $_");
	put_test("ls $_ test test $nothing test test test");
	put_test("ls \"test\"\"test1\"test2");
	put_test("ls \"$USER\"");
	put_test("ls tests$USER");
	put_test("ls tests$USER$USER$USER¥");
	put_test("ls test$USER$USERtest");
	put_test("ls > $USER");
	put_test("ls > $para");
	put_test("ls > $$USER");
	put_test("ls  $nothing test");
	put_test("ls  \'$nothing\'");
	put_test("ls  \'$USER\'");
	put_test("ls  test\'$USER\'test");
	put_test("ls  test$nothing$USER");
	put_test("echo \'\"\'\'$PATH\'\'\"\'");
	put_test("echo \'\"\'$USER\'\"\'");
	return (0);	
}