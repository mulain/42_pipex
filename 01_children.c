/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_children.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:14:21 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/19 21:55:28 by wmardin          ###   ########.fr       */
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
void	firstchild(t_envl *e)
{
	e->pid[0] = fork();
	if (e->pid[0] == -1)
		error_fork();
	if (e->pid[0] == 0)
	{
		dup2(e->file1, STDIN_FILENO);
		dup2(e->pipe[1], STDOUT_FILENO);
		execve(e->cmdpaths[0], e->input[0], e->env);
	}
}
