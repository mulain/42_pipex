/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:42:22 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/17 10:53:41 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
Returns a 3d array with the split up commands.
Array level 3: pointers to each command string "sentence", i.e. 2d array.
Array level 2: The chain of strings (sentence) from each commmand
Array level 1: The single words from each command sentence.

Figuring out the correct numbers for the arguments from argv:
input			pipex	file1	cmd_1	cmd_2	cmd_3	file2
index in argv	argv_0	argv_1	argv_2	argv_3	argv_4	argv_5
argc_position	argc_1	argc_2	argc_3	argc_4	argc_5	argc_6

cmd_n		cmd_last		file2
argv_n+1 	argv_argc-2		argv_argc-1
argc_n+2

malloc n = argc - 3 because:
-1 for program name
-1 for file 1
-1 for file 2
*/
char	***get_commands(int argc, char **argv)
{
	char	***commands;
	int		i;
	int		j;

	commands = malloc((argc - 3) * sizeof(char **));
	i = 2;
	while (i < argc - 1)
	{
		commands[i - 2] = ft_split(argv[i], ' ');
		i++;
	}
	i = 0;
	j = 0;
	printf("%s\n", commands[0][0]);
	while (j < argc - 3)
	{
		free(commands[j][0]);
		j++;
	}
	return (commands);
}
