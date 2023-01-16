/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:26:02 by tasano            #+#    #+#             */
/*   Updated: 2023/01/16 16:02:01 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	builtin_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
		printf("%s\n", getcwd(NULL, 0));
	return (0);
}
