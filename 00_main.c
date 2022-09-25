/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 09:53:29 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/25 23:30:28 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
Mac leakcheck:
leaks -atExit -- ./pipex file1 "cmd1" "cmd2" file2

***************************************************************************
Lookup table for numbers for the arguments from argv:
---No here_doc---
input:			pipex	infile	cmd_1	cmd_2	cmd_3	outfile
index in argv:	argv_0	argv_1	argv_2	argv_3	argv_4	argv_5
argc_value:		argc_1	argc_2	argc_3	argc_4	argc_5	argc_6

cmd_n		cmd_last		outfile
argv_n+1 	argv_argc-2		argv_argc-1
argc_n+2

---Yes here_doc---
input:			pipex	heredoc	limiter	cmd_1	cmd_2	cmd_3	outfile
index in argv:	argv_0	argv_1	argv_2	argv_3	argv_4	argv_5	argv_6
argc_value:		argc_1	argc_2	argc_3	argc_4	argc_5	argc_6	argc_7
***************************************************************************
while loop children limitation:
-1 for program name
-1 for infile / here_doc
(-1 for limiter if here_doc -> subtract here_doc value)
-1 for lastchild (after loop)
-1 for outfile
*/
int	main(int argc, char **argv, char **env)
{
	t_envl		e;
	int			i;

	setup(&e, argc, argv, env);
	get_infile(&e);
	i = 0;
	firstchild(&e, i);
	i++;
	while (i < argc - 4 - e.here_doc)
	{
		middlechild(&e, i);
		i++;
	}
	lastchild(&e, i);
	shutdown(&e);
	return (0);
}

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

void	get_cmd(t_envl *e, int i)
{
	int		j;

	if (!access(e->input[i][0], X_OK))
	{
		e->command = ft_strdup(e->input[i][0]);
		return ;
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
		return ;
	write(2, e->input[i][0], ft_strlen(e->input[i][0]));
	write(2, ": command not found\n", 20);
	e->command = ft_strdup(e->input[i][0]);
	close(e->curr_pipe[1]);
}
