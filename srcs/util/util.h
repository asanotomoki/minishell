/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 23:54:22 by tasano            #+#    #+#             */
/*   Updated: 2022/12/13 16:03:36 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

#include <stdio.h>
int		err_msg(char *msg);
int		perr_msg(char *msg);
void	 free_args(char **cmd_paths);
#endif
