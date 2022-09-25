/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 10:20:42 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/25 22:18:45 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H
# include "libft/include/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <string.h>

typedef struct envelope
{
	int		argc;
	char	**argv;
	char	**env;
	int		here_doc;
	char	*tempfile;
	int		infile;
	int		outfile;
	pid_t	pid;
	int		exitstatus;
	int		pipes[2][2];
	int		*curr_pipe;
	int		*prev_pipe;
	char	***input;
	char	**env_paths;
	char	*command;
}	t_envl;

//00_main.c
int		main(int argc, char **argv, char **env);
void	get_infile(t_envl *e);
void	get_here_doc(t_envl *e);
void	get_cmd(t_envl *e, int i);

//01_children.c
void	firstchild(t_envl *e, int i);
void	middlechild(t_envl *e, int i);
void	lastchild(t_envl *e, int i);
void	wait_child(t_envl *e);

//02_utils.c
void	rotate_pipes(t_envl *e);
void	redirect_io(t_envl *e, int input, int output);

//06_setup_1.c
void	setup(t_envl *e, int argc, char **argv, char **env);
void	split_input_cmds(t_envl *e);
void	split_env_path(t_envl *e);

//07_shutdown.c
void	shutdown(t_envl *e);
void	free3d_char(char ***array);
void	free2d_char(char **array);

//08_errors.c
void	error_argumentcount(void);
void	error_msg_exit(t_envl *e, char *msg);

//09_helperfunctions.c
void	print3d(char ***array);
void	print2d(char **array);
void	printpipefd(int	*pipe, int i);

#endif