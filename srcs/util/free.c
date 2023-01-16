/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:15:57 by tasano            #+#    #+#             */
/*   Updated: 2023/01/16 20:36:45 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

void	free_strval(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}

void	free_args(char ***input)
{
	char 	**argv;
	size_t	i;

	if (!input)
		return ;
	argv = *input;
	i = 0;
	while (argv[i])
	{
		free_strval(&argv[i]);
		i++;
	}
	argv = NULL;
	free(argv);
}
