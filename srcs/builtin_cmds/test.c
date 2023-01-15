/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:10:26 by tasano            #+#    #+#             */
/*   Updated: 2023/01/15 16:58:30 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmds.h"
#include "libft.h"
#include "leakdetect.h"
 #include <stdlib.h>
#include <stdio.h>
#include "leakdetect.h"

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

int main()
{
	leak_detect_init();

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
}