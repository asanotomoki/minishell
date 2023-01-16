/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:45:00 by tasano            #+#    #+#             */
/*   Updated: 2023/01/17 04:02:41 by tasano           ###   ########.fr       */
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
