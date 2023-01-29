/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:25:12 by tasano            #+#    #+#             */
/*   Updated: 2023/01/21 11:00:52 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "builtin_cmds.h"
#include "util.h"
#include "libft.h"

int	builtin_env(void)
{
	t_list	*environ;

	environ = get_env();
	while (environ)
	{
		printf("%s\n", (char *)environ->content);
		environ = environ->next;
	}
	return (0);
}
