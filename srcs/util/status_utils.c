/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:45:00 by tasano            #+#    #+#             */
/*   Updated: 2023/01/19 00:30:29 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_status(void)
{
	return (g_shell.status);
}

void	set_status(int status)
{
	g_shell.status = status;
}

int	set_get_status(int status)
{
	set_status(status);
	return (get_status());
}
