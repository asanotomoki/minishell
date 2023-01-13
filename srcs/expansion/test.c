/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:19:06 by tasano            #+#    #+#             */
/*   Updated: 2023/01/14 00:08:44 by hiroaki          ###   ########.fr       */
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

void put_token_lst(t_token_lst *content)
{
	while (content)
	{
		if (content->type == PIPE)
			printf ("PIPE : ");
		else if (content->type == OUTREDIRECT)
			printf ("OUTREDIRECT : ");
		else if (content->type == OUTADDITION)
			printf ("OUTADDITION : ");
		else if (content->type == INREDIRECT)
			printf ("INREDIRECT : ");
		else if (content->type == HEREDOCU)
			printf ("HEREDOCU : ");
		else if (content->type == EXPANDABLE)
			printf ("EXPANDABLE : ");
		else if (content->type == NON_EXPANDABLE)
			printf ("NON_EXPANDABLE : ");
		printf("%s\n", content->token);
		content = content->next;
	}
}

int put_test(char *input)
{
	t_cmd *cmd;

	printf("\n------- [ %s ] -------\n", input);
	cmd = parser(lexer(input));
<<<<<<< .merge_file_A1td1q
	//expansion(cmd);
=======
	expansion(cmd);
>>>>>>> .merge_file_J570wC
	return (put_ans(cmd));
}

int main()
{
	//put_test("ls -l < test1|\">|||||grep lexer\" > test2 >> test3 | wc -l | cat");
	//put_test("ls -l | wc -l | cat >> test");
	put_test("ls $USER");
	put_test("ls \"test\"\"test1\"test2");
	put_token_lst (lexer("ls \"test\"\"test1\"test2"));
	put_test("ls \"$USER\"");
	put_test("ls tests$USER");
	put_test("ls tests$USER$USER$USER¥");
	put_test("ls test$USER$USERtest");
	put_test("ls > $USER");
	put_test("ls > $para");
	put_test("ls > $$USER");
<<<<<<< .merge_file_A1td1q
	put_test("ls  $nothing");
	put_test("ls  \'$nothing\'");
	put_test("ls  test$nothing$USER");
	put_test("echo \'\"\'$PATH\'\"\'");
=======
	put_test("ls  $nothing test");
	put_test("ls  \'$nothing\'");
	put_test("ls  test$nothing$USER");
	put_test("echo \'\"\'\'$PATH\'\'\"\'");
>>>>>>> .merge_file_J570wC
	////error test
	//put_test("ls -l ||");
	//put_test("ls -l <<");
	//put_test("ls -l << <");
	return (0);
}
