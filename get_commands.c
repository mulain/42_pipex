/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:42:22 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/16 19:35:27 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
pipex	file1	cmd1	cmd2	cmdn		cmdlast			file2
argv_0	argv_1	argv_2	argv_3	argv_n+1 	argv_argc-1		argv_argc
*/
char	***get_commands(int argc, char **argv)
{
	char	***commands;
	int		i;

	commands = malloc((argc - 2) * sizeof(char **));
	i = 2;
	while (i < argc)
	{
		commands[i - 2] = ft_split(argv[i], ' ');
		i++;
	}
	return (commands);
}
