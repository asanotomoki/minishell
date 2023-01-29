/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 10:02:16 by tasano            #+#    #+#             */
/*   Updated: 2023/01/21 09:07:05 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include "util.h"
#include "minishell.h"
#include <stdlib.h>

int	put_parse_error(char *param)
{
	ft_putstr_fd(SHELL, 2);
	ft_putstr_fd(": syntax error near unexpected token ", 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(param, 2);
	ft_putendl_fd("'", 2);
	set_status(258);
	return (258);
}

void	all_free(t_cmd *cmd, t_token_lst *lst)
{
	token_lstfree(&lst);
	cmd_lstfree(&cmd);
}

int	parse_error(t_token_lst *lst, t_cmd **cmd, t_token_lst **head)
{
	int	flag;

	flag = 0;
	if (lst->type == OUTREDIRECT || lst->type == OUTADDITION || \
	lst->type == INREDIRECT || lst->type == HEREDOCU)
	{
		if (!lst->next)
			flag = put_parse_error("newline");
		else if (lst->next->type != EXPANDABLE)
			flag = put_parse_error(lst->next->token);
	}
	else if (lst->type == PIPE)
	{
		if (!lst->next)
			flag = put_parse_error("|");
		else if (lst->next->type == PIPE)
			flag = put_parse_error("|");
	}
	if (flag)
		all_free(*cmd, *head);
	return (flag);
}

void	free_parser_lst(t_token_lst **lst)
{
	t_token_lst	*tmp;

	tmp = *lst;
	while (tmp)
	{
		*lst = tmp->next;
		if (tmp->type != EXPANDABLE)
			free_strval(&tmp->token);
		free(tmp);
		tmp = NULL;
		tmp = *lst;
	}
}
