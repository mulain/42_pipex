/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_children.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:14:21 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/21 21:26:41 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
The call:

fid = dup2(fildes, fildes2);
is equivalent to:

close(fildes2);
fid = fcntl(fildes, F_DUPFD, fildes2);
with the following exceptions:

If fildes2 is negative or greater than or equal to OPEN_MAX,
the dup2() function returns a value of -1 and sets errno to EBADF.
If fildes is a valid file descriptor and is equal to fildes2,
the dup2() function returns fildes2 without closing it.
If fildes is not a valid file descriptor, dup2() fails and does
not close fildes2.
If successful, dup2() returns a value that is equal to the value of fildes2.
If a failure occurs, it returns a value of -1.

fid = dup2(fildes, fildes2);
PARAMETERS
fildes	Is the file descriptor to duplicate.
fildes2	Is the file descriptor that fildes is duplicated onto.
*/
void	firstchild(t_envl *e, int i)
{
	if (pipe(e->pipe[i]) == -1)
		error_pipe(e);
	e->pid = fork();
	if (e->pid == -1)
		error_fork(e);
	if (e->pid == 0)
	{
		close(e->pipe[i][0]);
		dup2(e->file1, STDIN_FILENO);
		close(e->file1);
		dup2(e->pipe[i][1], STDOUT_FILENO);
		close(e->pipe[i][1]);
		execve(e->cmdpaths[i], e->input[i], e->env);
	}
	else
	{
		wait_child(e);
		close(e->file1);
		close(e->pipe[i][1]);
	}
}

void	middlechild(t_envl *e, int i)
{
	if (pipe(e->pipe[i]) == -1)
		error_pipe(e);
	e->pid = fork();
	if (e->pid == -1)
		error_fork(e);
	if (e->pid == 0)
	{
		dup2(e->pipe[i - 1][0], STDIN_FILENO);
		close(e->pipe[i - 1][0]);
		dup2(e->pipe[i][1], STDOUT_FILENO);
		close(e->pipe[i][1]);
		execve(e->cmdpaths[i], e->input[i], e->env);
	}
	else
	{
		wait_child(e);
		close(e->pipe[i - 1][0]);
		close(e->pipe[i][1]);
	}
}

/*
cmd_n		cmd_last		file2
argv_n+1 	argv_argc-2		argv_argc-1
argc_n+2
Last child doesn't need to make another pipe:
reads from previous child's read end and writes to file2.
*/
void	lastchild(t_envl *e, int i)
{
	e->pid = fork();
	if (e->pid == -1)
		error_fork(e);
	if (e->pid == 0)
	{
		dup2(e->pipe[i - 1][0], STDIN_FILENO);
		close(e->pipe[i - 1][0]);
		dup2(e->file2, STDOUT_FILENO);
		close(e->file2);
		execve(e->cmdpaths[i], e->input[i], e->env);
	}
	else
	{
		wait_child(e);
		close(e->pipe[i - 1][0]);
		close(e->file2);
	}
}

void	wait_child(t_envl *e)
{
	waitpid(e->pid, &e->exitstatus, 0);
	if (!WIFEXITED(e->exitstatus))
		error_waitpid(e);
}
