/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main+setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 09:53:29 by wmardin           #+#    #+#             */
/*   Updated: 2022/11/12 20:08:25 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
Mac leakcheck:
leaks -atExit -- ./pipex file1 "cmd1" "cmd2" file2

***************************************************************************
Lookup table for numbers for the arguments from argv:
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
while loop children limitation:
-1 for program name
-1 for infile / here_doc
(-1 for limiter if here_doc -> subtract here_doc value)
(-1 for firstchild, but i starts at 1)
-1 for lastchild (after loop)
-1 for outfile
*/
int	main(int argc, char **argv, char **env)
{
	t_envl		e;
	int			i;

	setup(&e, argc, argv, env);
	get_infile(&e);
	firstchild(&e, 0);
	i = 1;
	while (i < argc - 4 - e.here_doc)
	{
		middlechild(&e, i);
		i++;
	}
	get_outfile(&e);
	lastchild(&e, i);
	shutdown(&e);
	return (0);
}

void	setup(t_envl *e, int argc, char **argv, char **env)
{
	if (argc < 5)
		error_argumentcount();
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		if (argc < 6)
			error_argumentcount();
		e->here_doc = 1;
		e->tempfile = "here_doc.tmp";
	}
	else
	{
		e->here_doc = 0;
		e->tempfile = NULL;
	}
	e->argc = argc;
	e->argv = argv;
	e->env = env;
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
-1 for infile
-1 for outfile
+1 for NULL
We want to skip the first 2 entries (i = n = 2) and the last (i < argc-1):
they are not execve commands.

Yes here_doc:
malloc argc - n; n = 3 because:
-1 for program name
-1 for here_doc
-1 for limiter
-1 for outfile
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
