/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 09:53:29 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/21 17:21:01 by wmardin          ###   ########.fr       */
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

leaks -atExit -- ./pipex file1 "string1 a b c" "string2 ab cd ef" "string3 knudel hair shmudel" file2
int dup(int oldfd);
int dup2(int oldfd, int newfd);
*/
int	main(int argc, char **argv, char **env)
{
	t_envl		e;
	//char		buffer[1000];
	int			i;

	//close opened pipes if later pipe fails oO
	//printf("pipe 0 0:%i\n", e.pipe[0][0]);
	//printf("pipe 0 1:%i\n", e.pipe[0][1]);


	setup(&e, argc, argv, env);
	open_files(&e);
	i = 0;
	firstchild(&e, i);

	i++;
	while (i < argc - 4)
	{
		middlechild(&e, i);
		i++;
	}
	lastchild(&e, i);



	close(e.file1);
	close(e.file2);
	//close(e.pipe[0]);
	//close(e.pipe[1]);

	/* waitpid(e.pid[1], e.exitstatus, 0);
	if (WIFEXITED(*e.exitstatus))
		printf("Child 2 with PID %i exited successfully.\n", e.pid[1]);
	else
		error_waitpid(); */

	//read(e.pipe[0], buffer, 1000);
	//printf("knudel:%s\n", buffer);

	free3d(e.input);
	free2d(e.cmdpaths);
	free2d(e.env_paths);
	return (0);
}

/*
while (i > argc - 3)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			error_fork();
		if (pid[i] == 0)
		{
			//run process 1
			close(fd[0]); //close read end
			execve(e.cmdpaths[i], e.input, env);
			close(fd[1]);
		}
		close(fd[1]); //close write end on parent side
		waitpid(pid[i], NULL, 0) //wait for child i

*/
