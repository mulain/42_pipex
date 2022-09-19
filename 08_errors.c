/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:19:10 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/19 14:08:56 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_pipe(void)
{
	perror("Pipe");
	exit(EXIT_FAILURE);
}

void	error_fork(void)
{
	perror("Fork");
	exit(EXIT_FAILURE);
}

void	error_path(void)
{
	perror("Command path");
	exit(EXIT_FAILURE);
}

void	error_file1(void)
{
	perror("File1");
	exit(EXIT_FAILURE);
}

void	error_file2(void)
{
	perror("File2");
	exit(EXIT_FAILURE);
}