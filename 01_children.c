/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_children.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:14:21 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/27 23:16:07 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	firstchild(t_envl *e, int i)
{
	if (pipe(e->curr_pipe) == -1)
		error_msg_exit(e, "pipe");
	get_cmd(e, i);
	e->pid = fork();
	if (e->pid == -1)
		error_msg_exit(e, "fork");
	if (e->pid == 0)
	{
		close(e->curr_pipe[0]);
		redirect_io(e, e->infile, e->curr_pipe[1]);
		execve(e->command, e->input[i], e->env);
		error_execve(e, i);
	}
	else
	{
		wait_child(e);
		close(e->infile);
		close(e->curr_pipe[1]);
		if (e->command)
			free(e->command);
		e->command = NULL;
		rotate_pipes(e);
	}
}

void	middlechild(t_envl *e, int i)
{
	if (pipe(e->curr_pipe) == -1)
		error_msg_exit(e, "pipe");
	get_cmd(e, i);
	e->pid = fork();
	if (e->pid == -1)
		error_msg_exit(e, "fork");
	if (e->pid == 0)
	{
		redirect_io(e, e->prev_pipe[0], e->curr_pipe[1]);
		execve(e->command, e->input[i], e->env);
		error_execve(e, i);
	}
	else
	{
		wait_child(e);
		close(e->prev_pipe[0]);
		close(e->curr_pipe[1]);
		if (e->command)
			free(e->command);
		e->command = NULL;
		rotate_pipes(e);
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
	get_cmd(e, i);
	e->pid = fork();
	if (e->pid == -1)
		error_msg_exit(e, "fork");
	if (e->pid == 0)
	{
		redirect_io(e, e->prev_pipe[0], e->outfile);
		execve(e->command, e->input[i], e->env);
		error_execve(e, i);
	}
	else
	{
		wait_child(e);
		close(e->prev_pipe[0]);
		close(e->outfile);
		if (e->command)
			free(e->command);
		e->command = NULL;
	}
}

void	wait_child(t_envl *e)
{
	if (waitpid(e->pid, &e->exitstatus, WNOHANG) == -1)
		error_msg_exit(e, "waitpid");
}

void	redirect_io(t_envl *e, int input, int output)
{
	if (dup2(input, STDIN_FILENO) == -1)
		error_msg_exit(e, "redirect input");
	close(input);
	if (dup2(output, STDOUT_FILENO) == -1)
		error_msg_exit(e, "redirect output");
	close(output);
}
