/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:10:26 by tasano            #+#    #+#             */
/*   Updated: 2022/12/29 16:11:35 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	t_token_lst	*content;
	t_token_lst	*tmp;
	char input[] = "ls -l < test|\'|||||grep lexer\'> $test >>test$test1 | wc -l | cat <<\"test";
 
	content = lexer(input);
	tmp = content;
	printf("%s\n", input);
	while (content)
	{
		if (content->type == PIPE)
			printf ("PIPE : ");
		else if (content->type == OUTREDIRECT)
			printf ("OUTREDIRECT : ");
		else if (content->type == OUTADDITION)
			printf ("OUTADDITION : ");
		else if (content->type == INREDIRECT)
			printf ("INREDIRECT : ");
		else if (content->type == HEREDOCU)
			printf ("HEREDOCU : ");
		else if (content->type == EXPANDABLE)
			printf ("EXPANDABLE : ");
		else if (content->type == NON_EXPANDABLE)
			printf ("NON_EXPANDABLE : ");
		printf("%s\n", content->token);
		content = content->next;
	}
	token_lstfree(&tmp);
	
	return (0);	
}