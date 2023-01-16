/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:10:26 by tasano            #+#    #+#             */
/*   Updated: 2023/01/16 21:42:26 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "lexer.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

void execve_test(char *test_command)
 {
	char *input;
	t_token_lst *lst;

	lst = NULL;
	lexer(test_command, &lst);
	printf("\n-----");
	input = strdup(test_command);
	printf(" [ %s ] ------\n", input);

	exection(parser(lst));
	free(input);

}

 int main()
{
	/*****---------basic test----------*****/
	execve_test(" wc -l > test1 < result.log");
	execve_test("ls -l | wc");
	execve_test("ls -l > test2 | wc -l");
	execve_test("ls -l | grep exec |  wc -l");
	execve_test("cat test1");
	execve_test("./bash.sh");
	execve_test("cat | ls");
	//execve_test("ls > test > test1 << EOF << EOT < test3 > test1 < test");

	/*****---------addition test----------*****/
	int fd = open("test4",  O_WRONLY);
	write (fd, "\n--------test4 result--------\n", 30);
	close(fd);
	execve_test("ls -l >> test4");


	/*****---------special test----------*****/
	execve_test("wc -l > test1 < result.log");
	execve_test("> test2 < result.log");

	/*****---------builtins test----------*****/
	execve_test("cd ../");

	/*****---------error test----------*****/
	printf("\n--------error test----------\n");
	execve_test("bash.sh");
	execve_test("cat nosuchfile");
	execve_test("wc -l < nosuchfile");
	execve_test("wc -l < permissionfile");
	execve_test("nocommand | nocommand");
	return (0);
}
