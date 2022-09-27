/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:19:10 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/27 23:21:24 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_argumentcount(void)
{
	write(2, "Too few arguments.\n", 19);
	exit(EXIT_FAILURE);
}

void	error_msg_exit(t_envl *e, char *msg)
{
	perror(msg);
	shutdown(e);
	exit(EXIT_FAILURE);
}

void	error_execve(t_envl *e, int i)
{
	write(2, e->input[i][0], ft_strlen(e->input[i][0]));
	write(2, ": command not found\n", 20);
	shutdown(e);
	exit(EXIT_FAILURE);
}
