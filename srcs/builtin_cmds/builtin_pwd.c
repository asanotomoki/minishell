/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tasano <tasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:26:02 by tasano            #+#    #+#             */
/*   Updated: 2023/01/12 11:13:10 by tasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

ino_t get_inode(char *);
void printpathto(ino_t);
void inum_to_name(ino_t, char *, int );

int main()
{
    printpathto( get_inode( "." ) ); /* ここまでのパスを出力する */
    putchar('\n');
    return 0;
}

void printpathto( ino_t this_inode )
/*
 * this_inodeに対応するディレクトリまでのパスを出力する再帰関数
 */
{
    ino_t my_inode ;
    char its_name[BUFSIZ];

    if ( get_inode("..") != this_inode )
    {
        chdir( ".." );          /* 1つ上のディレクトリへ */

        inum_to_name(this_inode, its_name, BUFSIZ); /* 名前を取得 */

        my_inode = get_inode( "." ); /* 再帰的に */
        printpathto( my_inode );     /* 1つ上のディレクトリ */
        printf("/%s", its_name );     /* までを出力 */
    }                                /* このディレクトリの名前を出力 */
}

void inum_to_name(ino_t inode_to_find, char *namebuf, int buflen)
/* カレントディレクトリから引数のiノード番号を持つファイル */
/* (サブディレクトリ)を探し、名前をnamebufにコピーする */
{
    DIR *dir_ptr;               /* ディレクトリ */
    struct  dirent *direntp;    /* 各エントリ */

    dir_ptr = opendir( "." );
    if ( dir_ptr == NULL ) {
        perror( "." );
        return ;
    }

    /* 指定されたiノード番号を持つファイル(サブディレクトリ)を探す */
    while ( ( direntp = readdir( dir_ptr ) ) != NULL )
        if ( direntp->d_ino == inode_to_find )
        {
            strncpy( namebuf, direntp->d_name, buflen);
            namebuf[buflen-1] = '\0'; /* 念の為 */
            closedir( dir_ptr );
            return;
        }
    fprintf(stderr, "error looking for inum %llu\n", inode_to_find);
    return ;
}

ino_t get_inode( char *fname )
/* ファイルのiノード番号を返す */
{
    struct stat info;

    if ( stat( fname, &info ) == -1 ) {
        fprintf(stderr, "Cannot stat ");
        perror(fname);
        return (info.st_ino);
    }

    return info.st_ino;
}