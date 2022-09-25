/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_children.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:14:21 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/25 18:35:03 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	firstchild(t_envl *e, int i)
{
	if (pipe(e->now_pipe) == -1)
		error_msg_exit(e, "pipe");
	e->pid = fork();
	if (e->pid == -1)
		error_msg_exit(e, "fork");
	if (e->pid == 0)
	{
		close(e->now_pipe[0]);
		redirect_io(e, e->infile, e->now_pipe[1]);
		execve(e->cmdpaths[i], e->input[i], e->env);
	}
	else
	{
		wait_child(e);
		close(e->now_pipe[1]);
		rotate_pipes(e);
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

void	wait_child(t_envl *e)
{
	waitpid(e->pid, &e->exitstatus, 0);
	if (!WIFEXITED(e->exitstatus))
		error_msg_exit(e, "waitpid");
}
