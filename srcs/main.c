/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:01:21 by asanotomoki       #+#    #+#             */
/*   Updated: 2023/01/19 02:06:26 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "exec.h"
#include "lexer.h"
#include "parser.h"
#include "minishell.h"
#include "expansion.h"
#include "builtin_cmds.h"

static int	shell_system(char *line)
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
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

static void	interactive_shell(void)
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

static void	init_shell(void)
{
	init_env();
	g_shell.status = 0;
	g_shell.sig_no = 0;
	g_shell.child_interrupted = 0;
	g_shell.heredoc_interrupted = 0;
}

int	main(void)
{
	init_shell();
	catch_signal();
	set_rl_routine();
	interactive_shell();
	return (g_shell.status);
}
