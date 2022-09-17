/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:42:22 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/17 20:08:48 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
Returns a 3d array with the split up commands.
Array level 3: Array of the command string "sentences".
Array level 2: Array of the words from each commmand (single sentence).
Array level 1: Array of the chars from each word (single words).

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
void	parse(t_envl *e, int argc, char **argv, char **env)
{
	int		i;

	e->argc = argc;
	e->argv = argv;
	e->env = env;
	parse_cmds(e);
}

void	split_input(t_envl *e)
{
	int		i;

	i = 0;
	e->input = malloc((e->argc - 3) * sizeof(char **));
	i = 2;
	while (i < e->argc - 1)
	{
		e->input[i - 2] = ft_split(e->argv[i], ' ');
		i++;
	}
}

void	split_path(t_envl *e)
{
	int		i;

	i = 0;
	
}
