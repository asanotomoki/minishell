/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:10:17 by asanotomoki       #+#    #+#             */
/*   Updated: 2022/12/13 16:15:33 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

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
