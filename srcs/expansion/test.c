/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:10:26 by tasano            #+#    #+#             */
/*   Updated: 2023/01/16 20:12:52 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "minishell.h"
#include "util.h"
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
	t_token_lst *lst;

	printf("\n------- [ %s ] -------\n", input);
	lst = NULL;
	lexer(input, &lst);
	cmd = parser(lst);
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

	put_test("ls  $nothing");
	put_test("ls  \'$nothing\'");
	put_test("ls  test$nothing$USER");
	put_test("echo \'\"\'$PATH\'\"\'");

	put_test("ls  $nothing test");
	put_test("ls  \'$nothing\'");
	put_test("ls  test$nothing$USER");
	put_test("echo \'\"\'\'$PATH\'\'\"\'");
	//set_status(128);
	g_shell.status = 10;
	put_test("echo $?");
	////error test
	//put_test("ls -l ||");
	//put_test("ls -l <<");
	//put_test("ls -l << <");
	return (0);
}

