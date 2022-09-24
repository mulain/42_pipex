/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_setup_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:28:51 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/24 12:00:08 by wmardin          ###   ########.fr       */
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
