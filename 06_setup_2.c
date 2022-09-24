/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_setup_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:28:51 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/24 10:10:59 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
Instead of making a pipe for each process, re-use old int array?
Would need
	int	pipe[2][2]
and a reference for each 1d array:
	int	*pipe_a (starts as pipe_a = pipe[0])
	int *pipe_b	(starts as pipe_b = pipe[1])
then switch between pipe_a and pipe_b...
Meh...

number of pipes is argc - n; n = 4 because:
-1 for program name
-1 for infile
-1 for last child
-1 for oufile
If using here_doc, argc - n; n= 5 because:
-1 for program name
-1 for here_doc
-1 for limiter
-1 for last child
-1 for outfile
*/
void	allocate_pipes(t_envl *e)
{
	int		i;
	//int		n;

	/* if (e->here_doc)
		n = 5;
	else
		n = 4;
	e->pipe = malloc((e->argc - n) * sizeof(int *)); */
	e->pipe = malloc((e->argc - e->n) * sizeof(int *));
	i = 0;
	while (i < e->argc - e->n)
	{
		e->pipe[i] = malloc(2 * sizeof(int));
		i++;
	}
}

/*
chmod 0644 -> user has read / write (4 + 2 + 0)
others only have read (4 + 0 + 0)

If using here_doc:
-	opens (i.e. creates) a temporary file instead of opening infile
-	Uses getnextline to read until a delimiter is encountered
-	opens file 2 in create read/write and append(!) mode
	decimal used to save a space because of the norm (line length) (0644 = 420)

No here_doc:
-	opens infile (argv[1]) in read only mode in fd e.infile
-	opens outfile (argv[argc-1]) in create read/write and truncate mode
*/
void	open_files(t_envl *e)
{
	if (e->here_doc)
	{
		e->infile = open("here_doc_tempfile", O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (e->infile == -1)
			error_infile(e);
		e->outfile = open(e->argv[e->argc - 1],
				O_CREAT | O_RDWR | O_APPEND, 420);
		if (e->outfile == -1)
			error_outfile(e);
	}
	else
	{
		e->infile = open(e->argv[1], O_RDONLY);
		if (e->infile == -1)
			error_infile(e);
		e->outfile = open(e->argv[e->argc - 1],
				O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (e->outfile == -1)
			error_outfile(e);
	}
}
