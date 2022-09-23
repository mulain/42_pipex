/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 20:31:35 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/23 20:36:33 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
---Input table for heredoc---
input:			pipex	heredoc	limiter	cmd_1	cmd_2	cmd_3	file2
index in argv:	argv_0	argv_1	argv_2	argv_3	argv_4	argv_5	argv_6
argc_value:		argc_1	argc_2	argc_3	argc_4	argc_5	argc_6	argc_7

Checks if delimiter (and only delimiter) was received from gnl, if so, breaks.
If not, writes what was received from gnl to the heredoc in appendmode
*/
void	here_doc(t_envl *e)
{
	char	*line;

	e->file1 = open("here_doc_tempfile", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (e->file1 == -1)
		error_here_doc_tempfile(e);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (!ft_strncmp(line, e->argv[2], ft_strlen(e->argv[2]))
			&& line[ft_strlen(e->argv[2])] == '\n'
			&& line[ft_strlen(e->argv[2]) + 1] == 0)
			break ;
		write(e->file1, line, ft_strlen(line));
		line = get_next_line(STDIN_FILENO);
	}
}
