/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:01:21 by asanotomoki       #+#    #+#             */
/*   Updated: 2023/01/17 15:23:19 by hiroaki          ###   ########.fr       */
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

int	interactive_shell(void)
{
	char	*line;
	int		status;

	status = 0;
	while (1)
	{
		line = readline(PROMPT);
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			status = shell_system(line);
		}
		free(line);
	}
	return (status);
}

void	init_shell(void)
{
	init_env();
	set_status(0);
}

int	main(void)
{
	//setup_sigint();
	init_shell();
	interactive_shell();
	return (0);
}
