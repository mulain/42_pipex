/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 09:53:29 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/19 22:17:32 by wmardin          ###   ########.fr       */
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
	char		buffer[1000];
	//int			i;

	setup(&e, argc, argv, env);
	open_files(&e);
	if (pipe(e.pipe) == -1)
		error_pipe();
	firstchild(&e);
	waitpid(e.pid[0], e.exitstatus, 0);
	if (e.exitstatus)
		error_cmdexecution();

	/* dup2(e.file1, e.pipe[1]);
	i = 0;

	pid[i] = fork();
	if (pid[i] == -1)
		error_fork();
	if (pid[i] == 0)
	{
		//run process 1
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]); //close read end
		close(fd[1]);
		execve(e.cmdpaths[i], e.input[i], env);
	} */
	//[1]); //close write end on parent side
	read(e.pipe[0], buffer, 1000);
	printf("knudel:%s\n", buffer);
	/* array[0] = "usr/bin/which";
	array[1] = "ls";
	array[2] = NULL; */
	/* pid = fork();
	if (pid == -1)
		error_fork();
	if (pid == 0)
	{
		execve("/usr/bin/which", array, env);
	} */
	/*
	pid1 = fork();
	if (pid1 == -1)
		error_fork();
	if (pid1 == 0)
	{
		printf("child\n");
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(argv[1], (char *const *)argv[2], NULL);
	}

	pid2 = fork();
	if (pid2 == -1)
		error_fork();
	if (pid2 == 0)
	{
		printf("child2\n");
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(argv[4], (char *const *)argv[3], NULL);
	}
	close(fd[0]);
	close(fd[1]);
	printf("%s\n", argv[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0); */
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
