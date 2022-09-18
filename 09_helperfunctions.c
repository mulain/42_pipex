/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_helperfunctions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 19:50:17 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/18 23:20:21 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
Prints a 3d char array. Must be NULL terminated.
*/
void	print3d(char ***array)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (array[j])
	{
		ft_printf("---Cmd %i---\n", j);
		while (array[j][i])
		{
			ft_printf("%s\n", array[j][i]);
			i++;
		}
		i = 0;
		j++;
	}
}

/*
Prints a 2d char array. Must be NULL terminated.
*/
void	print2d(char **array)
{
	int		i;

	i = 0;
	while (array[i])
	{
		ft_printf("---Cmd %i---\n", i);
		ft_printf("%s\n", array[i]);
		i++;
	}
}

void	free3d(char ***array)
{
	int		i;
	int		j;

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

void	free2d(char **array)
{
	int		i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}