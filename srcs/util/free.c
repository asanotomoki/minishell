/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:15:57 by tasano            #+#    #+#             */
/*   Updated: 2022/12/14 12:35:19 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

void free_args(char **cmd_paths)
{
	size_t	i;

	i = -1;
	if (!cmd_paths)
		return ;
	while (cmd_paths[++i])
	{
		free(cmd_paths[i]);
		cmd_paths = NULL;
	}
	cmd_paths = NULL;
	free(cmd_paths);
}
