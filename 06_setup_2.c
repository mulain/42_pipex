/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_setup_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:28:51 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/25 17:20:52 by wmardin          ###   ########.fr       */
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

	e->pipe = malloc((e->argc - e->n) * sizeof(int *));
	i = 0;
	while (i < e->argc - e->n)
	{
		e->pipe[i] = malloc(2 * sizeof(int));
		i++;
	}
}

void	check_here_doc(t_envl *e)
{
	if (!ft_strncmp(e->argv[1], "here_doc", 9))
	{
		e->here_doc = 1;
		e->tempfile = "here_doc.tmp";
}

/*
bash will open the outfile even if the commands won't execute.
So have to move this up here and close the fd again after the
file was made.
*/
void	open_files_prematurely(t_envl *e)
{
	if (e->here_doc)
		e->outfile = open(e->argv[e->argc - 1], O_CREAT | O_RDWR
				| O_APPEND, 0644);
	else
		e->outfile = open(e->argv[e->argc - 1], O_CREAT | O_RDWR
				| O_TRUNC, 0644);
	if (e->outfile == -1)
		error_msg_exit(e, e->argv[e->argc - 1]);
	close(e->outfile);
}
