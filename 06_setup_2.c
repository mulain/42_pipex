/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_setup_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:28:51 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/21 21:44:04 by wmardin          ###   ########.fr       */
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
-1 for program name
-1 for file 1
-1 for last child
-1 for file 2
*/
void	allocate_pipes(t_envl *e)
{
	int		i;

	i = 0;
	e->pipe = malloc((e->argc - 4) * sizeof(int *));
	while (i < e->argc - 4)
	{
		e->pipe[i] = malloc(2 * sizeof(int));
		i++;
	}
}

void	open_files(t_envl *e)
{
	e->file1 = open(e->argv[1], O_RDONLY);
	if (e->file1 == -1)
		error_file1(e);
	e->file2 = open(e->argv[e->argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (e->file2 == -1)
		error_file2(e);
}
