/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:19:10 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/16 18:27:05 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_pipe(void)
{
	perror("Pipe failed.\n");
	exit(EXIT_FAILURE);
}

void	error_fork(void)
{
	perror("Fork failed.\n");
	exit(EXIT_FAILURE);
}
