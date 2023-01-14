/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:22:15 by tasano            #+#    #+#             */
/*   Updated: 2023/01/14 05:15:27 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXPANSION_H
# define EXPANSION_H

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include <errno.h>

int expansion(t_cmd *cmd);
char *heredoc_expand(char *str);

//utils
char **swap_cmd_null(char **cmd, size_t i);
char *set_return_val(char *str);
void free_strval(char **str);
int set_mode(char c, int mode);

//parameter
char *set_parameter(char *str, size_t i);

//remove_quote
char *remove_quote(char *str);
#endif
