/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 00:16:16 by hiroaki           #+#    #+#             */
/*   Updated: 2023/01/18 00:17:20 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rl_event(void)
{
	extern int	_rl_echo_control_chars;

	_rl_echo_control_chars = 0;
	if (g_shell.sig_no != SIGINT)
		return (0);
	g_shell.sig_no = 0;
	g_shell.status = 1;
	rl_done = 1;
	rl_redisplay();
	return (1);
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

void	trap_signal(void)
{
	g_shell.sig_no = 0;
	g_shell.heredoc_sig_flag = 0;
	rl_event_hook = rl_event;
	init_sigaction();
}
