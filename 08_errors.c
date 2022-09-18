/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:19:10 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/18 09:44:13 by wmardin          ###   ########.fr       */
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
	perror("Search command path");
	exit(EXIT_FAILURE);
}
