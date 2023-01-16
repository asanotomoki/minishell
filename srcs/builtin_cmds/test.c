/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:10:26 by tasano            #+#    #+#             */
/*   Updated: 2023/01/16 16:52:36 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmds.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

int export_test(char *input)
{
	builtin_export(ft_split(input, ' '));
	return (0);
}
int echo_test(char *input)
{
	builtin_echo(ft_split(input, ' '));
	return (0);
}

int main()
{
	init_env();
	export_test("export USER=tomo USER+=tomoki SHELL=minishell =test");
	//builtin_env();
	builtin_unset(ft_split("unset tes:t", ' '));
	builtin_unset(ft_split("unset USER HOME", ' '));
	printf("%s\n", getenv("USER"));
	printf("%s\n", getenv("HOME"));
	echo_test("echo test msg");
	echo_test("echo");
	echo_test("echo -n");
	//echo_test("echo -n test msg");
	//builtin_exit(1, ft_split("exit", ' '));
	//builtin_exit(2, ft_split("exit 80", ' '));
	//builtin_exit(2, ft_split("exit 0", ' '));
	//builtin_exit(2, ft_split("exit 213713802", ' '));
	//builtin_exit(4, ft_split("exit 80 0 1", ' '));
	//builtin_exit(2, ft_split("exit aa", ' '));
	//builtin_exit(2, ft_split("exit -1000", ' '));
	//builtin_cd(ft_split("cd ", ' '));
	//builtin_pwd();
	//builtin_cd(ft_split("cd nothing", ' '));
	//builtin_pwd();
	//builtin_cd(ft_split("cd ./test.dSYM/Contents/Resources/../", ' '));
	//builtin_pwd();
	//builtin_env();
	//printf("PWD=%s\n", getenv("PWD"));
	//builtin_cd(ft_split("cd ./testdir", ' '));
	return (0);
}