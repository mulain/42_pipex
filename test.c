/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 20:05:01 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/23 19:39:07 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(void)
{
	char	*line;
	int		fd;
	int		i;

	i = 1;
	fd = open("file1", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		ft_printf("line %i:\"%s\"\n", i, line);
		line = get_next_line(fd);
		i++;
	}
}
