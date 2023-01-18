/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 00:16:16 by hiroaki           #+#    #+#             */
/*   Updated: 2023/01/19 03:22:47 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "util.h"
#include "minishell.h"

void	ignore_signal(int sig_no)
{
	struct sigaction	sa_ignore;

	sa_ignore.sa_handler = SIG_IGN;
	sa_ignore.sa_flags = 0;
	sigemptyset(&sa_ignore.sa_mask);
	if (sigaction(sig_no, &sa_ignore, NULL) != 0)
		perror_exit(EXIT_FAILURE, "sigaction");
}

void	signal_handler(int sig_no)
{
	g_shell.sig_no = sig_no;
}

void	init_sigaction(void)
{
	struct sigaction	parent_act;
	struct sigaction	child_act;

	sigemptyset(&parent_act.sa_mask);
	sigemptyset(&child_act.sa_mask);
	parent_act.sa_flags = 0;
	child_act.sa_flags = SA_NOCLDWAIT;
	parent_act.sa_handler = signal_handler;
	child_act.sa_handler = signal_handler;
	sigaction(SIGINT, &parent_act, NULL);
	sigaction(SIGCHLD, &child_act, NULL);
}

void	catch_signal(void)
{
	init_sigaction();
	ignore_signal(SIGQUIT);
}
