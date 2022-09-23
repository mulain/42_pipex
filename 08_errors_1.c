/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_errors_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:19:10 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/23 22:03:08 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_pipe(t_envl *e)
{
	perror("pipe");
	cleanup(e);
	exit(EXIT_FAILURE);
}

void	error_fork(t_envl *e)
{
	perror("fork");
	cleanup(e);
	exit(EXIT_FAILURE);
}

void	error_path(t_envl *e)
{
	perror("command path");
	cleanup(e);
	exit(EXIT_FAILURE);
}

void	error_file1(t_envl *e)
{
	perror(e->argv[1]);
	cleanup(e);
	exit(EXIT_FAILURE);
}

void	error_file2(t_envl *e)
{
	perror(e->argv[e->argc - 1]);
	cleanup(e);
	exit(EXIT_FAILURE);
}
