/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 10:20:42 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/18 23:18:39 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H
# include "libft/include/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/errno.h>
# include <string.h>

typedef struct envelope
{
	int		argc;
	char	**argv;
	char	**env;
	char	***input;
	char	**env_paths;
	char	**cmdpaths;
}	t_envl;

//00_main.c

//01_parse.c
void	parse(t_envl *e, int argc, char **argv, char **env);
void	split_input(t_envl *e);
void	split_env_path(t_envl *e);
void	get_cmdpaths(t_envl *e);
int		get_singlepath(t_envl *e, int i);

//08_errors.c
void	error_pipe(void);
void	error_fork(void);
void	error_path(void);

//09_helperfunctions.c
void	print3d(char ***array);
void	print2d(char **array);
void	free3d(char ***array);
void	free2d(char **array);
#endif