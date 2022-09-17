/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helperfunctions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 19:50:17 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/17 09:41:58 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print3darray(int argc, char ***array)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < argc - 3)
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

void	free3darray(int argc, char ***array)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < argc - 3)
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
