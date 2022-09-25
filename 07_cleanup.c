/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:28:51 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/25 22:01:44 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
cleanup serves as a gathering point for all necessary cleanup functions.
Here, it is only one function, so it's kinda useless. Still kept it for
overall structure.
Actually ended up adding unlink, so yeah.
*/
void	cleanup(t_envl *e)
{
	free_mem(e);
	if (e->here_doc && !access(e->tempfile, F_OK))
		unlink(e->tempfile);
}

void	free_mem(t_envl *e)
{
	free3d_char(e->input);
	free2d_char(e->env_paths);
	if (e->command)
		free(e->command);
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
