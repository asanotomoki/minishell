/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 23:54:22 by tasano            #+#    #+#             */
/*   Updated: 2023/01/16 21:49:54 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

#include <stdio.h>
int		err_msg(char *msg);
int		perr_msg(char *msg);

void	free_strval(char **str);
void	free_args(char ***input);

int		get_status(void);
void	set_status(int status);

size_t	search_param(char **argv, char *param);
char	**get_env(void);
int		init_env(void);
char	*env_put_error(char *function, char *val);
#endif
