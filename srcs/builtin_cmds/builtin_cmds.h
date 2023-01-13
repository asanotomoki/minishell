/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 23:54:22 by tasano            #+#    #+#             */
/*   Updated: 2023/01/13 13:28:32 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_CMDS_H
# define BUILTIN_CMDS_H

#include <stdio.h>
#include <stddef.h>

int builtin_echo(char **argv);
int builtin_exit(size_t argc, char **argv);
int builtin_env();
int builtin_export(char **argv);
int builtin_pwd();
int builtin_unset(char **argv);
int builtin_cd(char **argv);

#endif
