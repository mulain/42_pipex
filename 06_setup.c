/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_setup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:42:22 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/25 23:38:44 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
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
yes here_doc: number of pipes is argc - n; n = 5 because:
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
	e->argc = argc;
	e->argv = argv;
	e->env = env;
	if (!ft_strncmp(e->argv[1], "here_doc", 9))
	{
		e->here_doc = 1;
		e->tempfile = "here_doc.tmp";
	}
	else
	{
		e->here_doc = 0;
		e->tempfile = NULL;
	}
	e->curr_pipe = e->pipes[0];
	e->prev_pipe = e->pipes[1];
	e->input = NULL;
	e->env_paths = NULL;
	e->command = NULL;
	split_input_cmds(e);
	split_env_path(e);
}

/*
Writes a 3d array with the split up commands to the struct.
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
	using delimiter ':'. Result is stored in e.path.
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
		error_msg_exit(e, "env");
	while (e->env[i] && ft_strncmp(e->env[i], "PATH=", 5))
		i++;
	if (!e->env[i])
		error_msg_exit(e, "env");
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
