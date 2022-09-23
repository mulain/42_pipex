/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 09:53:29 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/22 11:59:13 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
open, close, read, write, malloc, free, perror, strerror, access, dup, dup2,
execve, exit, fork, pipe, unlink, wait, waitpid

./pipex file1 cmd1 cmd2 file2
< file1 cmd1 | cmd2 > file2

./pipex infile "ls -l" "wc -l" outfile
< infile ls -l | wc -l > outfile

./pipex infile "grep a1" "wc -w" outfile
< infile grep a1 | wc -w > outfile

fd[1] is write end
fd[2] is read end

This:
$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
Should behave like:
< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2

leaks -atExit -- ./pipex file1 "cmd1" "cmd2" file2
int dup(int oldfd);
int dup2(int oldfd, int newfd);
*/
int	main(int argc, char **argv, char **env)
{
	t_envl		e;
	int			i;

	setup(&e, argc, argv, env);
	i = 0;
	firstchild(&e, i);
	i++;
	while (i < argc - 4)
	{
		middlechild(&e, i);
		i++;
	}
	lastchild(&e, i);
	cleanup(&e);
	return (0);
}
