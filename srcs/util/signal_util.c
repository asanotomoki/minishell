/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 00:16:16 by hiroaki           #+#    #+#             */
/*   Updated: 2023/01/21 08:06:41 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include "util.h"
#include "libft.h"
#include "minishell.h"

void	sigint_handler(int sig_no)
{
	g_shell.sig_no = sig_no;
}

static void	ignore_signal(int sig_no)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if (sigaction(sig_no, &act, NULL) != 0)
		perror_exit(EXIT_FAILURE, "sigaction");
}

static void	catch_sigint(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = sigint_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_NOCLDSTOP | SA_RESTART;
	if (sigaction(SIGINT, &act, NULL) != 0)
		perror_exit(EXIT_FAILURE, "sigaction");
}

void	catch_signal(void)
{
	catch_sigint();
	ignore_signal(SIGQUIT);
}
