/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:10:26 by tasano            #+#    #+#             */
/*   Updated: 2022/12/18 20:46:19 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>
#include <string.h>
#include "libft.h"

int main()
{
	t_token_list	*content;
	t_token	*token;

	content = token_lstnew(token_new(strdup("ls") , DABLEQUATE));
	//output -> ls
	printf("%s\n", content->token->word);
	token_list_free(content);
	token = NULL;
	content = token_lstnew(token);
	//output -> null
	printf("%s\n", content->token->word);
	//token_list_free(content);
	return (0);	
}