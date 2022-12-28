/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:38:18 by tasano            #+#    #+#             */
/*   Updated: 2022/12/28 09:28:23 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include <stdlib.h>
char **append_args(char **args, size_t argc, char *new)
{
	size_t i;
	char **res;

	res = (char **)malloc(sizeof(char *) * (argc + 1 + 1));
	if (!res)
		return (NULL);
	res[argc] = new;
	res[argc + 1] = NULL;
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

void all_free(t_cmd **cmd, t_token_lst **lst)
{
	t_cmd	*tmp;
	t_redirection *tmpredirect;
	
	tmp = *cmd;
	while (tmp)
	{
		*cmd = tmp->piped_cmd;
		while (tmp->output)
		{
			tmpredirect = tmp->output->next;
			free(tmp->output);
			tmp->output = NULL;
			tmp->output = tmpredirect;
		}
		while (tmp->input)
		{
			tmpredirect = tmp->input->next;
			free(tmp->input);
			tmp->input = NULL;
			tmp->input = tmpredirect;
		}
		if (tmp->cmd)
			free(tmp->cmd);
		tmp->argc = 0;
		tmp = NULL;
		tmp = *cmd;
	}
	token_lstfree(lst);
}

int	put_parse_error(char *msg)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("'", 2);
	return (258);
}

int parse_error(t_token_lst *lst, t_cmd *cmd, t_token_lst **tmplst)
{
	int flag;

	flag = 0;
	if (lst->type == OUTREDIRECT || lst->type == OUTADDITION || lst->type == INREDIRECT || lst->type == HEREDOCU)
	{
		if (!lst->next)
			flag = put_parse_error("newline");
		else if (lst->next->type == OUTREDIRECT || lst->next->type == OUTADDITION || lst->next->type == INREDIRECT || lst->next->type == HEREDOCU)
			flag = put_parse_error(lst->next->token);
	}
	else if (lst->type == PIPE && lst->next && lst->next->type == PIPE)
		flag = put_parse_error("|");
	else if (lst->type == PIPE && !lst->next)
		flag = put_parse_error("|");
	if (flag)
		all_free(&cmd, tmplst);
	return (flag);
}

void free_parser_lst(t_token_lst **lst)
{
	t_token_lst *tmp;

	tmp = *lst;
	while (tmp)
	{
		*lst = tmp->next;
		if (tmp->type == PIPE ||
			tmp->type == OUTREDIRECT || tmp->type == OUTADDITION ||
			tmp->type == INREDIRECT || tmp->type == HEREDOCU)
		{
			free(tmp->token);
			tmp->token = NULL;
		}
		free(tmp);
		tmp = NULL;
		tmp = *lst;
	}
}

t_cmd *parser(t_token_lst *lst)
{
	t_cmd *cmd;
	t_cmd *tmp;
	t_token_lst *tmplst;

	cmd = cmd_new();
	tmp = cmd;
	tmplst = lst;
	while (lst)
	{
		if (parse_error(lst, tmp, &tmplst))
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
	free_parser_lst(&tmplst);
	return (tmp);
}