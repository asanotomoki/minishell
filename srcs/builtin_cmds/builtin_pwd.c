/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:26:02 by tasano            #+#    #+#             */
/*   Updated: 2023/01/24 13:19:04 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

ino_t get_inode(char *);
void printpathto(ino_t);

static char *inum_to_name(ino_t inode_to_find)
{
	DIR *dirp;
	struct dirent *direntp;

	dirp = opendir(".");
	if (dirp == NULL)
	{
		perror(".");
		return (NULL);
	}
	while ((direntp = readdir(dirp)) != NULL)
	{
		if (get_inode(direntp->d_name) == inode_to_find)
		{
			closedir(dirp);
			return (ft_strdup(direntp->d_name));
		}
	}
	return (NULL);
}

ino_t get_inode(char *fname)
{
	struct stat info;

	if (stat(fname, &info) == -1)
		;
	return (info.st_ino);
}

void printpathto(ino_t this_inode)
{
	char *its_name;

	if (get_inode("..") != this_inode)
	{
		chdir("..");
		its_name = inum_to_name(this_inode);
		printf("%s\n", its_name);
		printpathto(get_inode("."));
		if (!its_name)
			return ;
		printf("/%s", its_name);
		chdir(its_name);
		free(its_name);
	}
}

int builtin_pwd(void)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
		printf("%s\n", pwd);
	else if (get_env_char("PWD"))
	{
		pwd = get_env_char("PWD");
		printf("%s\n", pwd);
	}
	else
	{
		if (get_inode("..") == get_inode("."))
			printf("/");
		else
			printpathto(get_inode("."));
		printf("\n");
	}
	return (0);
}
