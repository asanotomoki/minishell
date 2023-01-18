/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:01:21 by asanotomoki       #+#    #+#             */
/*   Updated: 2023/01/18 00:19:20 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin_cmds.h"
#include "lexer.h"
#include "parser.h"
#include "expansion.h"
#include "exec.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int	shell_system(char *line)
{
	t_token_lst	*lexer_lst;
	t_cmd		*cmd_lst;
	int			status;

	lexer_lst = NULL;
	status = lexer(line, &lexer_lst);
	if (status)
		return (set_get_status(status));
	cmd_lst = parser(lexer_lst);
	if (!cmd_lst)
		return (get_status());
	if (expansion(cmd_lst))
		return (set_get_status(1));
	return (exection(cmd_lst));
}

void	detect_eof(void)
{
	rl_cleanup_after_signal();
	ft_putendl_fd("exit", 2);
	exit(EXIT_FAILURE);
}

void	interactive_shell(void)
{
	char	*line;

	line = readline(PROMPT);
	if (line == NULL)
		return (detect_eof());
	add_history(line);
	if (*line)
		g_shell.status = shell_system(line);
	free(line);
	return (interactive_shell());
}

void	init_shell(void)
{
	init_env();
	set_status(0);
}

int	main(void)
{
	trap_signal();
	init_shell();
	interactive_shell();
	return (g_shell.status);
}
