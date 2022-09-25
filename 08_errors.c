/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_errors_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:19:10 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/25 20:44:12 by wmardin          ###   ########.fr       */
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
	cleanup(e);
	exit(EXIT_FAILURE);
}
