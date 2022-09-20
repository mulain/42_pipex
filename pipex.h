/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 10:20:42 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/20 14:33:05 by wmardin          ###   ########.fr       */
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
	char	***input;
	char	**env_paths;
	char	**cmdpaths;
	int		**pipe;
	int		exitstatus;
	pid_t	pid;
	int		file1;
	int		file2;
}	t_envl;

//00_main.c
int		main(int argc, char **argv, char **env);

//02_children.c
void	firstchild(t_envl *e, int i);
void	middlechild(t_envl *e, int i);
void	lastchild(t_envl *e, int i);
void	wait_child(t_envl *e);

//07_setup_1.c
void	setup(t_envl *e, int argc, char **argv, char **env);
void	split_input(t_envl *e);
void	split_env_path(t_envl *e);
void	get_cmdpaths(t_envl *e);
int		get_singlepath(t_envl *e, int i);

//07_setup_2.c
void	allocate_pipes(t_envl *e);
void	open_files(t_envl *e);

//08_errors_1.c
void	error_pipe(void);
void	error_fork(void);
void	error_path(void);
void	error_file1(void);
void	error_file2(void);

//08_errors_2.c
void	error_argumentcount(void);
void	error_waitpid(void);

//09_helperfunctions.c
void	print3d(char ***array);
void	print2d(char **array);
void	free3d(char ***array);
void	free2d(char **array);

#endif