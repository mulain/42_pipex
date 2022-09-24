/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_errors_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:19:10 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/24 13:26:58 by wmardin          ###   ########.fr       */
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

void	error_path_old(t_envl *e)
{
	perror(e->input[e->i][0]);
	cleanup(e);
	exit(EXIT_FAILURE);
}

void	error_path(t_envl *e)
{
	char	*msg;

	msg = ft_strjoin(e->input[e->i][0], ": command not found\n");
	write(2, msg, ft_strlen(msg));
	free(msg);
	cleanup(e);
	exit(EXIT_FAILURE);
}

void	error_infile(t_envl *e)
{
	perror(e->argv[1]);
	cleanup(e);
	exit(EXIT_FAILURE);
}
