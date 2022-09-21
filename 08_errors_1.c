/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_errors_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:19:10 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/21 17:37:52 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_pipe(void)
{
	perror("pipe");
	exit(EXIT_FAILURE);
}

void	error_fork(void)
{
	perror("fork");
	exit(EXIT_FAILURE);
}

void	error_path(void)
{
	perror("command path");
	exit(EXIT_FAILURE);
}

void	error_file1(void)
{
	perror("file1");
	exit(EXIT_FAILURE);
}

void	error_file2(void)
{
	perror("file2");
	exit(EXIT_FAILURE);
}