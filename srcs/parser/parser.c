/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:38:18 by tasano            #+#    #+#             */
/*   Updated: 2022/12/26 15:33:33 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
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

int parse_error()
{
	return (0);
}

t_cmd *parser(t_token_lst *lst)
{
	t_cmd	*cmd;
	t_cmd	*tmp;
	
	cmd = cmd_new();
	tmp = cmd;
	while (lst)
	{
		if (parse_error())
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
	return (tmp);
}