/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:38:18 by tasano            #+#    #+#             */
/*   Updated: 2022/12/26 17:36:35 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include <stdlib.h>
char **append_args(char **args , size_t argc, char *new)
{
	size_t	i;
	char	**res;

	res = (char **)malloc(sizeof(char *) * (argc + 1));
	if (!res)
		return (NULL);
	res[argc] = new;
	if (argc != 0)
	{
		i = 0;
		while (i < argc)
		{
			res[i] = args[i];
			i++;
		}
		free(args);
	}
	return (res);
}

void	all_free()
{
	
}

int parse_error(t_token_lst *lst)
{
	int flag;

	flag = 0;
	if (!lst->next)
	{
		if (lst->type == OUTREDIRECT || lst->type == OUTADDITION || lst->type == INREDIRECT || lst->type == HEREDOCU)
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
			flag = 1;
		}
	}
	if (lst->type == PIPE && lst->next && lst->next->type == PIPE)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		flag = 1;
	}
	if (flag)
		all_free();
	return (flag);
}

void	free_parser_lst(t_token_lst *lst)
{
	t_token_lst *tmp;
	while (lst)
	{
		tmp = lst->next;
		if (lst->type == PIPE || \
		lst->type == OUTREDIRECT || lst->type == OUTADDITION || \
		lst->type == INREDIRECT || lst->type == HEREDOCU)
		{
			free(lst->token);
			lst->token = NULL;
		}
		free(lst);
		lst = NULL;
		lst = tmp;
	}
}

t_cmd *parser(t_token_lst *lst)
{
	t_cmd	*cmd;
	t_cmd	*tmp;
	t_token_lst *tmplst;
	
	cmd = cmd_new();
	tmp = cmd;
	tmplst = lst;
	while (lst)
	{
		if (parse_error(lst))
			break ;
		if (lst->type == PIPE)
			cmd = cmd_addback(cmd, cmd_new());
		else if (lst->type == OUTREDIRECT || lst->type == OUTADDITION)
		{
			redirection_addback(&cmd->output, redirection_new(lst));
			lst = lst->next;
		}
		else if (lst->type == INREDIRECT || lst->type == HEREDOCU)
		{
			redirection_addback(&cmd->input, redirection_new(lst));
			lst = lst->next;
		}
		else
			cmd->cmd = append_args(cmd->cmd, cmd->argc++, lst->token);
		lst = lst->next;
	}
	free_parser_lst(tmplst);
	return (tmp);
}