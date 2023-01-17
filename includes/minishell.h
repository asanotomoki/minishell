/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:43:45 by asanotomoki       #+#    #+#             */
/*   Updated: 2023/01/18 00:05:55 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include "err.h"
# include "libft.h"
# include "util.h"

# define PROMPT "minish$ "
# define SHELL "minish"

typedef struct s_shell
{
	int						status;
	volatile sig_atomic_t	sig_no;
	volatile sig_atomic_t	heredoc_sig_flag;
}	t_shell;

t_shell	g_shell;

#endif
