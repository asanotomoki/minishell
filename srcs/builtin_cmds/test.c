/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:10:26 by tasano            #+#    #+#             */
/*   Updated: 2023/01/12 00:34:05 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cmds.h"
#include "libft.h"
#include <stdio.h>

int echo_test(char *input)
{
	builtin_echo(ft_split(input, ' '));
	return (0);
}

int main()
{
	echo_test("echo test msg");
	echo_test("echo");
	echo_test("echo -n");
	echo_test("echo -n test msg");
	return (0);	
}