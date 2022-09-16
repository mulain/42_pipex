/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:42:22 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/16 19:48:34 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
pipex	file1	cmd1	cmd2	cmd3	file2		cmdn		cmdlast			file2
argv_0	argv_1	argv_2	argv_3	argv_4	argv_5		argv_n+1 	argv_argc-2		argv_argc-1
argc_1	argc_2	argc_3	argc_4	argc_5	argc_6		argc_n+2
*/
char	***get_commands(int argc, char **argv)
{
	char	***commands;
	int		i;

	commands = malloc((argc - 3) * sizeof(char **));
	i = 2;
	while (i < argc - 1)
	{
		commands[i - 2] = ft_split(argv[i], ' ');
		i++;
	}
	return (commands);
}
