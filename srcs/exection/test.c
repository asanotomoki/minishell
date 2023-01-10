/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:10:26 by tasano            #+#    #+#             */
/*   Updated: 2023/01/10 23:44:47 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "lexer.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

 int	put_ans(int stat)
{
	//printf("\n%d\n", stat);
	stat += 1;
	return (stat);
 }

 int main(int argc, char **argv, char **envp)
{
	char *input;
	argc++;
	argv[0] = "test";
	printf("\n-----");
	input = strdup("wc -l > test1 < result.log");
	printf(" [ %s ] ------\n", input);
	put_ans(exection(parser(lexer(input)), envp));
	free(input);
	printf("\n-----");
	input = strdup("> test2 < result.log");
	printf(" [ %s ] ------\n", input);
	put_ans(exection(parser(lexer(input)), envp));
	free(input);
	printf("\n-----");
	input = strdup("ls -l | wc");
	printf(" [ %s ] ------\n", input);
	put_ans(exection(parser(lexer(input)), envp));
	free(input);
	printf("\n-----");
	int fd = open("test4", O_WRONLY);
	write (fd, "\n--------test4 result--------\n", 30);
	close(fd);
	input = strdup("ls -l >> test4");
	printf(" [ %s ] ------\n", input);
	put_ans(exection(parser(lexer(input)), envp));
	free(input);

	//error test
	//printf("\n-----");
	//input = strdup("ls -l ||");
	//printf(" [ %s ] ------\n", input);
	//put_ans(exection(parser(lexer(input)), envp));
	//free(input);
	//printf("\n-----");
	//input = strdup("ls -l <<");
	//printf(" [ %s ] ------\n", input);
	//put_ans(exection(parser(lexer(input)), envp));
	//printf("\n-----");
	//input = strdup("ls -l << <");
	//printf(" [ %s ] ------\n", input);
	//put_ans(exection(parser(lexer(input)), envp));
	//free(input);
	return (0);
}