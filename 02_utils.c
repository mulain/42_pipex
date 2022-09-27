/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 18:07:20 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/27 11:19:59 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_infile(t_envl *e)
{
	if (e->here_doc)
	{
		get_here_doc(e);
		e->infile = open(e->tempfile, O_RDONLY);
		if (e->infile == -1)
			error_msg_exit(e, "here_doc tempfile");
	}
	else
	{
		e->infile = open(e->argv[1], O_RDONLY);
		if (e->infile == -1)
			error_msg_exit(e, e->argv[1]);
	}
}

void	get_outfile(t_envl *e)
{
	if (e->here_doc)
		e->outfile = open(e->argv[e->argc - 1],
				O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		e->outfile = open(e->argv[e->argc - 1],
				O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (e->outfile == -1)
		error_msg_exit(e, e->argv[e->argc - 1]);
}

/*
---Input table for heredoc---
input:			pipex	heredoc	limiter	cmd_1	cmd_2	cmd_3	outfile
index in argv:	argv_0	argv_1	argv_2	argv_3	argv_4	argv_5	argv_6
argc_value:		argc_1	argc_2	argc_3	argc_4	argc_5	argc_6	argc_7

Checks if limiter (and only limiter) was received from gnl, if so, breaks.
If not, writes what was received from gnl to the heredoc in appendmode
*/
void	get_here_doc(t_envl *e)
{
	char	*line;

	e->infile = open(e->tempfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (e->infile == -1)
		error_msg_exit(e, e->tempfile);
	write (1, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (!ft_strncmp(line, e->argv[2], ft_strlen(e->argv[2]))
			&& line[ft_strlen(e->argv[2])] == '\n')
		{
			free(line);
			break ;
		}
		write(e->infile, line, ft_strlen(line));
		free(line);
		write (1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
	}
	close(e->infile);
}

int	get_cmd(t_envl *e, int i)
{
	int		j;

	if (!access(e->input[i][0], X_OK))
	{
		e->command = ft_strdup(e->input[i][0]);
		return (1);
	}
	j = 0;
	e->command = NULL;
	while (e->env_paths[j] && !e->command)
	{
		e->command = ft_strjoin(e->env_paths[j], e->input[i][0]);
		if (access(e->command, X_OK))
		{
			free(e->command);
			e->command = NULL;
		}
		j++;
	}
	if (e->command)
		return (1);
	write(2, e->input[i][0], ft_strlen(e->input[i][0]));
	write(2, ": command not found\n", 20);
	return (0);
}

void	rotate_pipes(t_envl *e)
{
	int		*temp;

	temp = e->prev_pipe;
	e->prev_pipe = e->curr_pipe;
	e->curr_pipe = temp;
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
