/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_children_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:14:21 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/23 20:10:39 by wmardin          ###   ########.fr       */
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

/*
---Yes here_doc---
input:			pipex	heredoc	limiter	cmd_1	cmd_2	cmd_3	file2
index in argv:	argv_0	argv_1	argv_2	argv_3	argv_4	argv_5	argv_6
argc_value:		argc_1	argc_2	argc_3	argc_4	argc_5	argc_6	argc_7

Allocates according the BUFFER_SIZE defined in getnextline (gnl).
Checks if delimiter (and only delimiter) was received from gnl, if so, breaks.
If not, writes what was received from gnl to the heredoc in appendmode
*/
void	firstchild_heredoc(t_envl *e, int i)
{
	char	*line;

	printf("heloo\n");
	e->file1 = open("here_doc_tempfile", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (e->file1 == -1)
		error_here_doc_tempfile(e);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (!ft_strncmp(line, e->argv[2], ft_strlen(e->argv[2])))
		{
			printf("limiter found %i\n %i\n", ft_strncmp(line, e->argv[2], ft_strlen(e->argv[2] + 1)), i);
			printf("strlenLimiter:%li\n", ft_strlen(e->argv[2]));
			break ;
		}
		write(e->file1, line, ft_strlen(line));
		line = get_next_line(STDIN_FILENO);
	}

	/* while (ft_strncmp(line, e->argv[2], ft_strlen(e->argv[2] + 1))
	{
		line = ft_strl get_next_line(STDIN_FILENO); */

}

void	wait_child(t_envl *e)
{
	waitpid(e->pid, &e->exitstatus, 0);
	if (!WIFEXITED(e->exitstatus))
		error_waitpid(e);
	ft_printf("Child with PID %i exited.\n", e->pid);
}
