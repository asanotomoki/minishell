/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:10:26 by tasano            #+#    #+#             */
/*   Updated: 2022/12/19 14:30:13 by tasano           ###   ########.fr       */
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

	content = token_lstnew(strdup("ls"), DABLEQUATE);
	token_lstadd_back(&content, token_lstnew(strdup("-l"), DABLEQUATE));
	token_lstadd_back(&content, token_lstnew(strdup("./srcs"), DABLEQUATE));
	token_lstadd_back(&content, token_lstnew(strdup(""), DABLEQUATE));
	//output -> ls -l ./srcs \0
	tmp = content;
	while (content)
	{
		printf("%s ", content->token);
		content = content->next;
	}
	token_lstfree(tmp);
	return (0);	
}