/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:28:51 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/21 21:30:30 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
cleanup serves as a gathering point for all necessary cleanup functions.
Here, it is only one function, so it's kinda useless. Still kept it for
overall structure.
*/
void	cleanup(t_envl *e)
{
	free_mem(e);
}

/*
	allocate_pipes(e);
	split_input(e);
	split_env_path(e);
	get_cmdpaths(e);

	Probably possible to make one free function per dimension and pass
	void pointer and size=sizeof(whateveristobefreed). Then instead of i++, use
	i += size. Would alsohave to end int array with NULL.
	Try out some time, but not now.
*/
void	free_mem(t_envl *e)
{
	free2d_int(e->pipe, e->argc - 4);
	free3d_char(e->input);
	free2d_char(e->env_paths);
	free2d_char(e->cmdpaths);
}

void	free3d_char(char ***array)
{
	int		i;
	int		j;

	if (!array)
		return ;
	i = 0;
	j = 0;
	while (array[j])
	{
		while (array[j][i])
		{
			free(array[j][i]);
			i++;
		}
		free(array[j]);
		i = 0;
		j++;
	}
	free(array);
}

void	free2d_char(char **array)
{
	int		i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free2d_int(int **array, int size)
{
	int		i;

	if (!array)
		return ;
	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
