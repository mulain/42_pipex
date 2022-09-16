/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 20:05:01 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/16 20:11:44 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	char	**array;
	int		i;

	i = 0;
	array = ft_split(argv[1], ' ');
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
