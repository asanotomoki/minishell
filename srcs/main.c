/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:01:21 by asanotomoki       #+#    #+#             */
/*   Updated: 2023/01/18 20:52:47 by hiroaki          ###   ########.fr       */
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
	exection(cmd_lst);
	return (get_status());
}

static void	detect_eof(void)
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
		shell_system(line);
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

void	set_rl_routine(void)
{
	extern int	_rl_echo_control_chars;

	_rl_echo_control_chars = 0;
	rl_event_hook = rl_routine;
}

int	main(void)
{
	init_shell();
	catch_signal();
	set_rl_routine();
	interactive_shell();
	return (g_shell.status);
}
