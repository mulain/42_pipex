/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_setup_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:28:51 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/20 13:53:15 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	allocate_pipes(t_envl *e)
{
	int		i;

	i = 0;
	e->pipe = malloc((e->argc - 3) * sizeof(int *));
	while (i < e->argc - 3)
	{
		e->pipe[i] = malloc(2 * sizeof(int));
		i++;
	}
}

void	open_files(t_envl *e)
{
	e->file1 = open(e->argv[1], O_RDONLY);
	if (e->file1 == -1)
		error_file1();
	e->file2 = open(e->argv[e->argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (e->file2 == -1)
		error_file2();
}
