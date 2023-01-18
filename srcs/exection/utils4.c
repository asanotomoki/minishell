/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 01:44:03 by hiroaki           #+#    #+#             */
/*   Updated: 2023/01/18 01:44:28 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

bool	heredoc_interrupted(void)
{
	if (g_shell.heredoc_sig_flag && g_shell.status)
	{
		g_shell.heredoc_sig_flag = 0;
		g_shell.status = 1;
		return (true);
	}
	return (false);
}
