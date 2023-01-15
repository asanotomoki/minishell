/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:10:26 by tasano            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/01/16 01:03:49 by tasano           ###   ########.fr       */
=======
/*   Updated: 2023/01/12 01:47:20 by tasano           ###   ########.fr       */
>>>>>>> 816db04 (exit)
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmds.h"
#include <stdio.h>


int echo_test(char *input)
{
	builtin_echo(ft_split(input, ' '));
	return (0);
}

int export_test(char *input)
{
	builtin_export(ft_split(input, ' '));
	return (0);
}

int init_env(char ***environ)
{
	size_t i;
	char **val;

	val = *environ;
	i = 0;
	while (val[i])
		i++;
	i = 0;
	while (val[i])
	{
		val[i] = ft_strdup(val[i]);
		if (!val[i])
		{
			perror("export");
			return (1);
		}
		i++;
	}
	return (0);
}

int echo_test(char *input)
{
	builtin_echo(ft_split(input, ' '));
	return (0);
}

int main()
{
<<<<<<< HEAD
	extern char **environ;
	char **val;
	val = (char **)environ;
	init_env(&val);
	leak_detect_check();
	//export_test("export USER=tomo USER+=tomoki SHELL=minishell =test");
	//builtin_env();
	builtin_unset(ft_split("unset USER", ' '));
	builtin_unset(ft_split("unset tes:t", ' '));
	printf("%s\n", getenv("USER"));
	builtin_env();
	leak_detect_check();
	return (0);
=======
	//echo_test("echo test msg");
	//echo_test("echo");
	//echo_test("echo -n");
	//echo_test("echo -n test msg");
	//builtin_exit(1, ft_split("exit", ' '));
	//builtin_exit(2, ft_split("exit 80", ' '));
	//builtin_exit(2, ft_split("exit 0", ' '));
	//builtin_exit(2, ft_split("exit 213713802", ' '));
	//builtin_exit(4, ft_split("exit 80 0 1", ' '));
	//builtin_exit(2, ft_split("exit -10", ' '));
	builtin_exit(2, ft_split("exit -1000", ' '));
	return (0);	
>>>>>>> 816db04 (exit)
}