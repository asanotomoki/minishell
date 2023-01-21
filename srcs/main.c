/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:01:21 by asanotomoki       #+#    #+#             */
/*   Updated: 2023/01/21 14:07:24 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "exec.h"
#include "util.h"
#include "lexer.h"
#include "parser.h"
#include "minishell.h"
#include "expansion.h"
#include "builtin_cmds.h"
#include "libft.h"

static int	shell_system(char *line)
{
	t_token_lst	*lexer_lst;
	t_cmd		*cmd_lst;
	int			status;

	lexer_lst = NULL;
	status = lexer(line, &lexer_lst);
	if (status != 0)
		return (set_get_status(status));
	cmd_lst = parser(lexer_lst);
	if (cmd_lst == NULL)
		return (get_status());
	status = expansion(cmd_lst);
	if (status != 0)
		return (set_get_status(status));
	status = exection(cmd_lst);
	cmd_lstfree(&cmd_lst);
	return (status);
}

void	detect_eof(void)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	ft_lstclear(&g_shell.env, free);
	exit(EXIT_SUCCESS);
}

static void	interactive_shell(void)
{
	char	*line;

	line = readline(PROMPT);
	if (line == NULL)
		return (detect_eof());
	if (*line)
	{
		add_history(line);
		shell_system(line);
	}
	free(line);
	return (interactive_shell());
}

static void	init_shell(void)
{
	init_env();
	g_shell.status = 0;
	g_shell.sig_no = 0;
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
