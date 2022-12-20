/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:10:26 by tasano            #+#    #+#             */
/*   Updated: 2022/12/20 15:42:14 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	t_token_lst	*content;
	t_token_lst	*tmp;

	content = lexer("ls -l | grep lexer | wc -l");
	tmp = content;
	while (content)
	{
		printf("%s\n", content->token);
		content = content->next;
	}
	token_lstfree(tmp);
	return (0);	
}