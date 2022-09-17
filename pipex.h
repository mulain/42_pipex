/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 10:20:42 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/17 10:57:59 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H
# include "libft/include/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/errno.h>
# include <string.h>

typedef struct envelope
{
	char	***input;
	int		argc;
}	t_envelope;

//errors.c
void	error_pipe(void);
void	error_fork(void);

//getcommands.c
char	***get_commands(int argc, char **argv);

//helperfunctions.c
void	print3darray(int argc, char ***array);
void	free3darray(int argc, char ***array);

#endif