/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_errors_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:19:10 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/19 22:21:58 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_argumentcount(void)
{
	write(2, "Too few arguments.\n", 19);
	exit(EXIT_FAILURE);
}

void	error_waitpid(void)
{
	perror("Waitpid");
	exit(EXIT_FAILURE);
}
