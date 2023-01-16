/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:01:21 by asanotomoki       #+#    #+#             */
/*   Updated: 2023/01/16 21:01:32 by hiroaki          ###   ########.fr       */
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

	lexer_lst = NULL;
	g_shell.status = lexer(line, &lexer_lst);
	if (g_shell.status)
		return (g_shell.status);
	cmd_lst = parser(lexer_lst);
	if (!cmd_lst)
		return (1);
	if (expansion(cmd_lst))
		return (1);
	return (exection(cmd_lst));
}

//static void	signal_inturrupt(int signo)
//{
//	(void)signo;
//
//	//rl_free_line_state();
//	//rl_cleanup_after_signal();
//	write(2, "exit\n", 5);
//	exit(1);
//}

//void ignore_signal(int signum)
//{
//	struct sigaction sa_ignore;
//
//	sa_ignore.sa_handler = SIG_IGN;
//	sa_ignore.sa_flags = 0;
//	sigemptyset(&sa_ignore.sa_mask);
//	sigaction(signum, &sa_ignore, NULL);
//}
//
//void	handler(int signum)
//{
//	(void)signum;
//}
//
//static void	setup_sigint(void)
//{
//	struct sigaction	sa;
//
//	sigemptyset(&sa.sa_mask);
//	sa.sa_flags = 0;
//	sa.sa_handler = handler;
//	sigaction(SIGINT, &sa, NULL);
//}
//
//void	setup_signal(void)
//{
//	setup_sigint();
//	ignore_signal(SIGINT);
//	rl_on_new_line();
//	//rl_replace_line();
//	rl_redisplay();
//}


int	main(int argc, char **argv)
{
	char	*line;

	(void)argv;
	(void)argc;

	//setup_sigint();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			shell_system(line);
		}
		free(line);
	}
	return (0);
}
