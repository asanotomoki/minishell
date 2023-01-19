/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 00:16:16 by hiroaki           #+#    #+#             */
/*   Updated: 2023/01/19 23:12:33 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include "util.h"
#include "libft.h"

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
	act.sa_flags = 0;
	if (sigaction(SIGINT, &act, NULL) != 0)
		perror_exit(EXIT_FAILURE, "sigaction");
}

static void	catch_sigchld(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = sigchld_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_NOCLDSTOP | SA_RESTART;
	if (sigaction(SIGCHLD, &act, NULL) != 0)
		perror_exit(EXIT_FAILURE, "sigaction");
}

void	catch_signal(void)
{
	catch_sigint();
	catch_sigchld();
	ignore_signal(SIGQUIT);
}
