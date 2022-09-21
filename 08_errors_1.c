/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_errors_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:19:10 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/21 19:40:40 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_pipe(t_envl *e)
{
	perror("pipe");
	shutdown(e);
	exit(EXIT_FAILURE);
}

void	error_fork(t_envl *e)
{
	perror("fork");
	shutdown(e);
	exit(EXIT_FAILURE);
}

void	error_path(t_envl *e)
{
	perror("command path");
	shutdown(e);
	exit(EXIT_FAILURE);
}

void	error_file1(t_envl *e)
{
	perror("file1");
	shutdown(e);
	exit(EXIT_FAILURE);
}

void	error_file2(t_envl *e)
{
	perror("file2");
	shutdown(e);
	exit(EXIT_FAILURE);
}