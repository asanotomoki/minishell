/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 23:54:22 by tasano            #+#    #+#             */
/*   Updated: 2022/12/17 22:10:46 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include <stdio.h>
#include <unistd.h>

typedef struct s_redirection
{
	int	fd;
} t_redirection;

typedef struct s_command_invocation
{
    t_redirection           *output_redirections;
    struct s_command_invocation    *piped_command;
    t_redirection           *input_redirections;
    const char                    **exec_and_args;
    pid_t                       pid;
}   t_command_invocation;


#endif
