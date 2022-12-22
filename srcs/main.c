/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test <test@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:01:21 by asanotomoki       #+#    #+#             */
/*   Updated: 2022/11/22 10:59:56 by tasano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin_cmds.h"
#include <readline/history.h>

static void shell_exit(char *line)
{
	printf("exit\n");
	free(line);
	exit(0);
}

int parser(char *line, char **envp)
{
	int	status;

	status = basic_cmd(line, envp);
	return (status);
}

int shell_system(char *line, char **envp)
{
	int	status;

	status = parser(line, envp);
	return (status);
}

int main(int argc, char **argv, char **envp)
{
	char *line;
	int status;

	if (argc < 1)
		return (1);
	status = 0;
	(void *)argv;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			status = 1;
			break;
		}
		if (!ft_strncmp("exit", line, 5))
		{
			shell_exit(line);
			break ;
		}
		if (*line)
		{
			add_history(line);
			//shell_system(line, envp);
		}
		free(line);
	}
	printf("test");
	return (status);
}