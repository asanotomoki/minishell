/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 23:54:22 by tasano            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/01/16 01:43:10 by tasano           ###   ########.fr       */
=======
/*   Updated: 2023/01/15 12:46:51 by tasano           ###   ########.fr       */
>>>>>>> d6cf5c8 (builtin unset)
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_CMDS_H
# define BUILTIN_CMDS_H

#include <stdio.h>
#include <stddef.h>
#include "leakdetect.h"
#define malloc(s) leak_detelc_malloc(s, __FILE__, __LINE__)
#define free leak_detect_free

<<<<<<< HEAD
int		builtin_echo(char **argv);
int		builtin_exit(size_t argc, char **argv);
int		builtin_env();
int		builtin_export(char **argv);
int		builtin_pwd();
int		builtin_unset(char **argv);
int		builtin_cd(char **argv);
=======
int builtin_echo(char **argv);
int builtin_exit(size_t argc, char **argv);
int builtin_env();
int builtin_export(char **argv);
int builtin_pwd();
int builtin_unset(char **argv);
int builtin_cd(char **argv);
size_t search_param(char **argv, char *param);
>>>>>>> d6cf5c8 (builtin unset)

#endif
