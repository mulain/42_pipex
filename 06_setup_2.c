/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_setup_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:28:51 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/22 22:48:04 by wmardin          ###   ########.fr       */
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

number of pipes is n = argc - 4 because:
-1 or program name
-1 for file 1
-1 for last child
-1 for file 2
If using here_doc, n = argc - 5 because:
-1 for program name
-1 for here_doc
-1 for delimiter
-1 for last child
-1 for file 2
*/
void	allocate_pipes(t_envl *e)
{
	int		i;

	if (e->here_doc)
		e->pipe = malloc((e->argc - 5) * sizeof(int *));
	else
		e->pipe = malloc((e->argc - 4) * sizeof(int *));
	i = 0;
	while (i < e->argc - 4)
	{
		e->pipe[i] = malloc(2 * sizeof(int));
		i++;
	}
}

/*
chmod 0644 -> user has read / write (4 + 2 + 0)
others only have read (4 + 0 + 0)

If using here_doc:
-	opens (i.e. creates) a temporary file instead of opening file1
-	Uses getnextline to read until a delimiter is encountered
-	opens file 2 in create read/write and append(!) mode
	decimal used to save a space because of the norm (line length) (0644 = 420)

No here_doc:
-	opens file 1 (argv[1]) in read only mode in fd e.file1
-	opens file 2 (argv[argc-1]) in create read/write and truncate mode
*/
void	open_files(t_envl *e)
{
	if (e->here_doc)
	{
		e->file1 = open("here_doc_tempfile", O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (e->file1 == -1)
			error_file1(e);
		e->file2 = open(e->argv[e->argc - 1], O_CREAT | O_RDWR | O_APPEND, 420);
		if (e->file2 == -1)
			error_file2(e);
	}
	/* else
	{
		e->file1 = open(e->argv[1], O_RDONLY);
		if (e->file1 == -1)
			error_file1(e);
		e->file2 = open(e->argv[e->argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (e->file2 == -1)
			error_file2(e);
	} */
}
