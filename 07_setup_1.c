/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_setup_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:42:22 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/19 22:13:29 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	setup(t_envl *e, int argc, char **argv, char **env)
{
	if (argc < 5)
		error_argumentcount();
	e->argc = argc;
	e->argv = argv;
	e->env = env;
	e->pid = malloc((argc - 3) * sizeof(pid_t));
	split_input(e);
	split_env_path(e);
	get_cmdpaths(e);
}

/*
Returns a 3d array with the split up commands.
Array level 3: Array of the command string "sentences".
Array level 2: Array of the words from each commmand (single sentence).
Array level 1: Array of the chars from each word (single words).

Figuring out the correct numbers for the arguments from argv:
input:			pipex	file1	cmd_1	cmd_2	cmd_3	file2
index in argv:	argv_0	argv_1	argv_2	argv_3	argv_4	argv_5
argc_value:		argc_1	argc_2	argc_3	argc_4	argc_5	argc_6

cmd_n		cmd_last		file2
argv_n+1 	argv_argc-2		argv_argc-1
argc_n+2

malloc n = argc - 2 because:
-1 for program name
-1 for file 1
-1 for file 2
+1 for NULL
*/
void	split_input(t_envl *e)
{
	int		i;

	e->input = malloc((e->argc - 2) * sizeof(char **));
	i = 2;
	while (i < e->argc - 1)
	{
		e->input[i - 2] = ft_split(e->argv[i], ' ');
		i++;
	}
	e->input[i - 2] = NULL;
}

/*
-	Iterates through env until the string starting with "PATH=" is found.
- 	Splits that string beginning at 5 bytes after the start to omit "PATH=".
	using delimiter ':'. Result ist stored in e.path.
-	If the resulting string doesn't end with "/", "/" is appended to create
	a valid path format.
*/
void	split_env_path(t_envl *e)
{
	int		i;
	int		len;
	char	*temp;

	i = 0;
	while (ft_strncmp(e->env[i], "PATH=", 5))
		i++;
	e->env_paths = ft_split(e->env[i] + 5, ':');
	i = 0;
	while (e->env_paths[i])
	{
		len = ft_strlen(e->env_paths[i]);
		if (e->env_paths[i][len - 1] != '/')
		{
			temp = e->env_paths[i];
			e->env_paths[i] = ft_strjoin(e->env_paths[i], "/");
			free(temp);
		}
		i++;
	}
}

/*
Iterates through the received commands.
Calls get_singlepath for each command to find the correct path / test if
there is a path. If no path is found, exits. If a path is found, get_singlepath
writes it to the struct. Ends with assigning a NULL pointer.
*/
void	get_cmdpaths(t_envl *e)
{
	int		i;

	e->cmdpaths = malloc((e->argc - 2) * sizeof(char *));
	i = 0;
	while (e->input[i])
	{
		if (get_singlepath(e, i))
			i++;
		else
			error_path();
	}
	e->cmdpaths[i] = NULL;
}

/*
Returns 1 if a valid path for the command of index i was found, 0 if not.
Joins env_paths[n] to the command until a valid command path is found or no
more paths exist to try.
-	uses access to determine if file exists and has exec rights
	-	if access != 0:
		-	frees and nulls
		-	increments j and tries the next command path
	-	if access = 0:
		- current command path is kept
		- the while condition !e.cmdpaths[i] breaks
Returns 1 or 0 depending on e.cmdpaths[i].
*/
int	get_singlepath(t_envl *e, int i)
{
	int		j;

	j = 0;
	e->cmdpaths[i] = NULL;
	while (e->env_paths[j] && !e->cmdpaths[i])
	{
		e->cmdpaths[i] = ft_strjoin(e->env_paths[j], e->input[i][0]);
		if (access(e->cmdpaths[i], X_OK))
		{
			free(e->cmdpaths[i]);
			e->cmdpaths[i] = NULL;
		}
		j++;
	}
	if (e->cmdpaths[i])
		return (1);
	return (0);
}
