/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:22:15 by tasano            #+#    #+#             */
/*   Updated: 2023/01/14 00:16:13 by hiroaki          ###   ########.fr       */
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
char *get_parameter(char *str);
void free_strval(char **str);
char *get_before(char *str, size_t len);
char *get_after(char *str, size_t len);
int is_expandble(char *str);
#endif
