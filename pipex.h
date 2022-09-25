/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 10:20:42 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/25 21:41:34 by wmardin          ###   ########.fr       */
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
	int		*prev_pipe;
	int		*curr_pipe;
	char	***input;
	char	**env_paths;
	char	*command;
}	t_envl;

//00_main.c
//int		main(int argc, char **argv, char **env);
void	get_infile(t_envl *e);
void	get_here_doc(t_envl *e);
void	get_cmd(t_envl *e, int i);

//01_children_1.c
void	firstchild(t_envl *e, int i);
void	middlechild(t_envl *e, int i);
void	lastchild(t_envl *e, int i);
void	open_input(t_envl *e);
void	wait_child(t_envl *e);

//02_utils.c
void	redirect_io(t_envl *e, int input, int output);
void	rotate_pipes(t_envl *e);

//02_here_doc.c
void	here_doc(t_envl *e);

//06_setup_1.c
void	setup(t_envl *e, int argc, char **argv, char **env);
void	split_input_cmds(t_envl *e);
void	split_env_path(t_envl *e);
void	allocate_pipes(t_envl *e);

//07_shutdown.c
void	cleanup(t_envl *e);
void	free_mem(t_envl *e);
void	free3d_char(char ***array);
void	free2d_char(char **array);
void	free2d_int(int **array, int size);

//08_errors_1.c
void	error_argumentcount(void);
void	error_msg_exit(t_envl *e, char *msg);


void	error_pipe(t_envl *e);
void	error_fork(t_envl *e);
void	error_path_old(t_envl *e);
void	error_path(t_envl *e);
void	error_infile(t_envl *e);

//08_errors_2.c
void	error_outfile(t_envl *e);
void	error_here_doc_tempfile(t_envl *e);
void	error_waitpid(t_envl *e);
void	error_env(t_envl *e);

//09_helperfunctions.c
void	print3d(char ***array);
void	print2d(char **array);
void	printpipefd(int	*pipe, int i);

#endif