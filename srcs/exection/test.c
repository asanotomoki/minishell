/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:10:26 by tasano            #+#    #+#             */
/*   Updated: 2023/01/16 01:45:22 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "lexer.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

void	execve_test(char *test_command, char **envp)
{
	char	*input;

	printf("\n-----");
	input = strdup(test_command);
	printf(" [ %s ] ------\n", input);
	exection(parser(lexer(input)), envp);
	free(input);

}

 int main(int argc, char **argv, char **envp)
{
	argc++;
	argv[0] = "test";

	/*****---------basic test----------*****/
	execve_test("cat << a | cat << b > tmp_file | ls", envp);
	execve_test(" wc -l > test1 < noting.log", envp);
	//execve_test("ls -l | wc", envp);
	//execve_test("ls -l > test2 | wc -l", envp);
	//execve_test("ls -l | grep exec |  wc -l", envp);
	//execve_test("cat test1", envp);
	//execve_test("./bash.sh", envp);

	/*****---------addition test----------*****/
	//int fd = open("test4",  O_WRONLY);
	//write (fd, "\n--------test4 result--------\n", 30);
	//close(fd);
	//execve_test("ls -l >> test4", envp);

	/*****---------special test----------*****/
	//execve_test("wc -l > test1 < result.log", envp);
	//execve_test("> test2 < result.log", envp);

	/*****---------builtins test----------*****/
	//execve_test("cd ../", envp);

	/*****---------error test----------*****/
	//printf("\n--------error test----------\n");
	//execve_test("bash.sh", envp);
	//execve_test("cat nosuchfile", envp);
	//execve_test("wc -l < nosuchfile", envp);
	//execve_test("wc -l < permissionfile", envp);
	//execve_test("wc -l > permissionfile", envp);
	//execve_test("nocommand | nocommand", envp);
	return (0);
}
