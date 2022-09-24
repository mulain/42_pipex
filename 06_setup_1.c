/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_setup_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:42:22 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/24 13:46:04 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
***************************************************************************
Lookup table for numbers for the arguments from argv:*****
---No here_doc---
input:			pipex	infile	cmd_1	cmd_2	cmd_3	outfile
index in argv:	argv_0	argv_1	argv_2	argv_3	argv_4	argv_5
argc_value:		argc_1	argc_2	argc_3	argc_4	argc_5	argc_6

cmd_n		cmd_last		outfile
argv_n+1 	argv_argc-2		argv_argc-1
argc_n+2

---Yes here_doc---
input:			pipex	heredoc	limiter	cmd_1	cmd_2	cmd_3	outfile
index in argv:	argv_0	argv_1	argv_2	argv_3	argv_4	argv_5	argv_6
argc_value:		argc_1	argc_2	argc_3	argc_4	argc_5	argc_6	argc_7
***************************************************************************

Vars that will later be malloc'd are nulled to protect the free functions
if shutdown occurs during an error and they haven't been malloc'd yet.

e.n is used to limit
- pipe allocation
- while loop for middlechildren
no here_doc: number of pipes is argc - n; n = 4 because:
-1 for program name
-1 for infile
-1 for last child
-1 for outfile
yes here_doc: number of pipes is argc - n; n= 5 because:
-1 for program name
-1 for here_doc
-1 for limiter
-1 for last child
-1 for outfile
*/
void	setup(t_envl *e, int argc, char **argv, char **env)
{
	if (argc < 5)
		error_argumentcount();
	e->pipe = NULL;
	e->input = NULL;
	e->env_paths = NULL;
	e->cmdpaths = NULL;
	e->argc = argc;
	e->argv = argv;
	e->env = env;
	open_files_prematurely(e);
	check_here_doc(e);
	allocate_pipes(e);
	split_input_cmds(e);
	split_env_path(e);
	get_cmdpaths(e);
}

/*
Returns a 3d array with the split up commands.
Array level 3: All command string "sentences" (text).
Array level 2: All words from each commmand (single sentence).
Array level 1: All chars from each word (single words).

No here_doc:
malloc argc - n; n = 2 because:
-1 for program name
-1 for file 1
-1 for file 2
+1 for NULL
We want to skip the first 2 entries (i = n = 2) and the last (i < argc-1):
they are not execve commands.

Yes here_doc:
malloc argc - n; n = 3 because:
-1 for program name
-1 for here_doc
-1 for delimiter
-1 for file 2
+1 for NULL
We want to skip the first 3 entries (i = n = 3) and the last (i < argc-1):
they are not execve commands.
*/
void	split_input_cmds(t_envl *e)
{
	int		i;
	int		n;

	if (e->here_doc)
		n = 3;
	else
		n = 2;
	e->input = malloc((e->argc - n) * sizeof(char **));
	i = n;
	while (i < e->argc - 1)
	{
		e->input[i - n] = ft_split(e->argv[i], ' ');
		i++;
	}
	e->input[i - n] = NULL;
}

/*
-	Iterates through env until the string starting with "PATH=" is found.
- 	Splits that string beginning at 5 bytes after the start to omit "PATH=".
	using delimiter ':'. Result ist stored in e.path.
-	If the resulting string doesn't end with "/", "/" is appended to create
	a valid path format.
	(In WSL2 on Win11 one path did already end with "/". Was a Windows path, but
	who knows...)
*/
void	split_env_path(t_envl *e)
{
	int		i;
	int		len;
	char	*temp;

	i = 0;
	if (!e->env)
		error_env(e);
	while (e->env[i] && ft_strncmp(e->env[i], "PATH=", 5))
		i++;
	if (!e->env[i])
		error_env(e);
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

No here_doc:
malloc argc - n; n = 2 because:
-1 for program name
-1 for file 1
-1 for file 2
+1 for NULL

Yes here_doc:
malloc argc - n; n = 3 because:
-1 for program name
-1 for here_doc
-1 for delimiter
-1 for file 2
+1 for NULL
*/
void	get_cmdpaths(t_envl *e)
{
	int		i;

	if (e->here_doc)
		e->cmdpaths = malloc((e->argc - 3) * sizeof(char *));
	else
		e->cmdpaths = malloc((e->argc - 2) * sizeof(char *));
	i = 0;
	while (e->input[i])
	{
		if (get_singlepath(e, i))
			i++;
		else
		{
			e->i = i;
			error_path(e);
		}
	}
	e->cmdpaths[i] = NULL;
}

/*
Returns 1 if a valid path for the command of index i was found, 0 if not.
Joins env_paths[n] to the command until a valid command path is found or no
more paths exist to try.
-	first checks if full cmd path was entered (i.e /usr/bin/ls)
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

	if (!access(e->input[i][0], X_OK))
	{
		e->cmdpaths[i] = ft_strdup(e->input[i][0]);
		return (1);
	}
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
