/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:48:36 by pbiederm          #+#    #+#             */
/*   Updated: 2022/08/04 13:15:13 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_err_infile(void)
{
	perror("No infile entered (infile cmd1 cmd2 outfile)");
	exit(701);
}

void	ft_err_pipe(void)
{
	perror("Pipe failed");
	exit(702);
}

void	ft_err_fork(void)
{
	perror("Fork failed");
	exit(703);
}

void	ft_err_ac(void)
{
	write(2, "Invalid input\n", 15);
	exit(2);
}
