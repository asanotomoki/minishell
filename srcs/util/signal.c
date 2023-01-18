/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 00:16:16 by hiroaki           #+#    #+#             */
/*   Updated: 2023/01/18 13:43:30 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include "minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <errno.h>

int	rl_event(void)
{
	extern int	_rl_echo_control_chars;

	_rl_echo_control_chars = 0;
	if (g_shell.sig_no != SIGINT)
		return (0);
	g_shell.sig_no = 0;
	if (g_shell.status == 0)
		g_shell.status = 100;
	rl_done = 1;
	rl_redisplay();
	return (0);
}
void ignore_signal(int signum)
{
	struct sigaction	sa_ignore;

	sa_ignore.sa_handler = SIG_IGN;
	sa_ignore.sa_flags = 0;
	sigemptyset(&sa_ignore.sa_mask);
	if (sigaction(signum, &sa_ignore, NULL) != 0)
		exit(1);
}

void	signal_handler(int signo)
{
	g_shell.sig_no = signo;
}

void	init_sigaction(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = signal_handler;
	sigaction(SIGINT, &sa, NULL);
}

//void	init_sigaction2(void)
//{
//	struct sigaction	sa2;
//
//	sigemptyset(&sa2.sa_mask);
//	sa2.sa_flags = 0;
//	sa2.sa_handler = signal_handler;
//	sigaction(SIGCHLD, &sa2, NULL);
//}

void	trap_signal(void)
{
	g_shell.sig_no = 0;
	g_shell.heredoc_sig_flag = 0;
	rl_outstream = stderr;
	//if (isatty(STDIN_FILENO))
	rl_event_hook = rl_event;
	ignore_signal(SIGQUIT);
	ignore_signal(SIGCHLD);
	init_sigaction();
}
