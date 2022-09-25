/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_children.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:14:21 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/25 10:59:39 by wmardin          ###   ########.fr       */
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
No "else" needed after firstchild_standard because execve is called.
*/
void	firstchild(t_envl *e, int i)
{
	if (pipe(e->pipe[i]) == -1)
		error_msg_exit(e, "pipe");
	e->pid = fork();
	if (e->pid == -1)
		error_msg_exit(e, "fork");
	if (e->pid == 0)
	{
		open_input(e);
		close(e->pipe[i][0]);
		dup2(e->infile, STDIN_FILENO);
		close(e->infile);
		dup2(e->pipe[i][1], STDOUT_FILENO);
		close(e->pipe[i][1]);
		execve(e->cmdpaths[i], e->input[i], e->env);
	}
	else
	{
		wait_child(e);
		close(e->pipe[i][1]);
	}
}

void	middlechild(t_envl *e, int i)
{
	if (pipe(e->pipe[i]) == -1)
		error_msg_exit(e, "pipe");
	e->pid = fork();
	if (e->pid == -1)
		error_msg_exit(e, "fork");
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
Last child doesn't need to make another pipe:
reads from previous child's read end and writes to outfile.
chmod 0644 -> user has read / write (4 + 2 + 0)
others only have read (4 + 0 + 0)
*/
void	lastchild(t_envl *e, int i)
{
	e->pid = fork();
	if (e->pid == -1)
		error_msg_exit(e, "fork");
	if (e->pid == 0)
	{
		if (e->here_doc)
			e->outfile = open(e->argv[e->argc - 1], O_CREAT | O_RDWR
					| O_APPEND, 0644);
		else
			e->outfile = open(e->argv[e->argc - 1], O_CREAT | O_RDWR
					| O_TRUNC, 0644);
		if (e->outfile == -1)
			error_msg_exit(e, e->argv[e->argc - 1]);
		dup2(e->pipe[i - 1][0], STDIN_FILENO);
		close(e->pipe[i - 1][0]);
		dup2(e->outfile, STDOUT_FILENO);
		close(e->outfile);
		execve(e->cmdpaths[i], e->input[i], e->env);
	}
	else
	{
		wait_child(e);
		close(e->pipe[i - 1][0]);
	}
}

void	open_input(t_envl *e)
{
	if (e->here_doc)
		e->infile = open(e->tempfile, O_RDONLY);
	else
		e->infile = open(e->argv[1], O_RDONLY);
	if (e->infile == -1)
		error_msg_exit(e, e->argv[1]);
}

void	wait_child(t_envl *e)
{
	waitpid(e->pid, &e->exitstatus, 0);
	if (!WIFEXITED(e->exitstatus))
		error_msg_exit(e, "waitpid");
}
