/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_shutdown.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:28:51 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/25 22:18:26 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	shutdown(t_envl *e)
{
	free3d_char(e->input);
	free2d_char(e->env_paths);
	if (e->command)
		free(e->command);
	if (e->here_doc && !access(e->tempfile, F_OK))
		unlink(e->tempfile);
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
