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
#include "lexer.h"
#include "parser.h"
#include "expansion.h"
#include "exec.h"
#include <readline/history.h>

int shell_system(char *line, char **envp)
{
	t_token_lst *lexer_lst;
	t_cmd 		*cmd_lst;

	lexer_lst = lexer(line);
	if (!lexer_lst)
		return (1);
	cmd_lst = parser(lexer_lst);
	if (!cmd_lst)
		return (1);
	if (expansion(cmd_lst))
		return (1);
	return (exection(cmd_lst, envp));
}

int main(int argc, char **argv, char **envp)
{
	char *line;
	
	argc++;
	(void)argv;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			return (1);
		if (*line)
		{
			add_history(line);
			shell_system(line, envp);
		}
		free(line);
	}
	return (0);
}