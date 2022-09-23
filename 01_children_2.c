/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_children_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:14:21 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/23 20:32:00 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	firstchild_standard(t_envl *e, int i)
{
	e->file1 = open(e->argv[1], O_RDONLY);
	if (e->file1 == -1)
		error_file1(e);
	close(e->pipe[i][0]);
	dup2(e->file1, STDIN_FILENO);
	close(e->file1);
	dup2(e->pipe[i][1], STDOUT_FILENO);
	close(e->pipe[i][1]);
	execve(e->cmdpaths[i], e->input[i], e->env);
}

void	wait_child(t_envl *e)
{
	waitpid(e->pid, &e->exitstatus, 0);
	if (!WIFEXITED(e->exitstatus))
		error_waitpid(e);
	ft_printf("Child with PID %i exited.\n", e->pid);
}
