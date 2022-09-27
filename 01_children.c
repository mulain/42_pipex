/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_children.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:14:21 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/27 12:14:25 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	firstchild(t_envl *e, int i)
{
	if (!get_cmd(e, i))
	{
		close(e->child_in);
		close(e->child_out);
		rotate_pipes(e);
		return ;
	}
	e->pid = fork();
	if (e->pid == -1)
		error_msg_exit(e, "fork");
	if (e->pid == 0)
	{
		close(e->curr_pipe[0]);
		redirect_io(e, e->child_in, e->child_out);
		execve(e->command, e->input[i], e->env);
	}
	else
	{
		parent(e);
		rotate_pipes(e);
	}
}

void	middlechild(t_envl *e, int i)
{
	if (!get_cmd(e, i))
	{
		close(e->child_in);
		close(e->child_out);
		rotate_pipes(e);
		return ;
	}
	e->pid = fork();
	if (e->pid == -1)
		error_msg_exit(e, "fork");
	if (e->pid == 0)
	{
		redirect_io(e, e->child_in, e->child_out);
		execve(e->command, e->input[i], e->env);
	}
	else
	{
		parent(e);
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
	if (!get_cmd(e, i))
	{
		close(e->child_in);
		close(e->child_out);
		return ;
	}
	e->pid = fork();
	if (e->pid == -1)
		error_msg_exit(e, "fork");
	if (e->pid == 0)
	{
		redirect_io(e, e->child_in, e->child_out);
		execve(e->command, e->input[i], e->env);
	}
	else
		parent(e);
}

void	parent(t_envl *e)
{
	if (waitpid(e->pid, &e->exitstatus, WNOHANG) == -1)
		error_msg_exit(e, "waitpid");
	close(e->child_in);
	close(e->child_out);
	if (e->command)
		free(e->command);
	e->command = NULL;
}
