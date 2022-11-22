/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:10:17 by asanotomoki       #+#    #+#             */
/*   Updated: 2022/11/22 11:07:11 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	perr_msg(char *msg)
{
	perror(msg);
	return (1);
}

int	err_msg(char *msg)
{
	ft_putendl_fd(msg, 2);
	return (1);
}
