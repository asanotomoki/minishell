/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 00:16:16 by hiroaki           #+#    #+#             */
/*   Updated: 2023/01/18 21:08:20 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include "minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <errno.h>

int	rl_routine(void)
{
	if (g_shell.sig_no == 0)
		return (0);
	if (g_shell.child_interrupted)
	{
		g_shell.status = 130;
		g_shell.child_interrupted = 0;
	}
	else
	{
		rl_done = 1;
		g_shell.status = 1;
		rl_redisplay();
	}
	g_shell.sig_no = 0;
	return (0);
}

void	ignore_signal(int signum)
{
	struct sigaction	sa_ignore;

	sa_ignore.sa_handler = SIG_IGN;
	sa_ignore.sa_flags = 0;
	sigemptyset(&sa_ignore.sa_mask);
	if (sigaction(signum, &sa_ignore, NULL) != 0)
		exit(EXIT_FAILURE);
	/* error_exitに変える */
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

void	signal_handler_for_child(int signo)
{
	g_shell.sig_no = signo;
}

void	init_sigaction_for_child(void)
{
	struct sigaction	sa2;

	sigemptyset(&sa2.sa_mask);
	sa2.sa_flags = SA_NOCLDWAIT;
	sa2.sa_handler = signal_handler_for_child;
	sigaction(SIGCHLD, &sa2, NULL);
}

void	catch_signal(void)
{
	ignore_signal(SIGQUIT);
	init_sigaction();
	init_sigaction_for_child();
}
