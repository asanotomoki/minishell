/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 00:16:16 by hiroaki           #+#    #+#             */
/*   Updated: 2023/01/19 17:04:58 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"

void	sigint_handler(int sig_no)
{
	g_shell.sig_no = sig_no;
}

void	sigchld_handler(int sig_no)
{
	int		status;

	(void)sig_no;
	while (waitpid(-1, &status, WNOHANG) > 0)
		g_shell.status = status >> 8;
}
