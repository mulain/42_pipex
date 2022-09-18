/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:49:21 by pbiederm          #+#    #+#             */
/*   Updated: 2022/08/04 12:47:40 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include "./libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <string.h>

void	ft_err_infile(void);
void	ft_err_ac(void);
void	ft_err_pipe(void);
void	ft_err_fork(void);
void	ft_err_ac(void);

struct	s_mediatior
{
	char	**p;
	char	**c;
	int		i;
	int		fd[2];
	int		pfd[2];
	int		a_c;
	int		status;
	int		id_greg;
	int		id_sara;
	int		err;
	int		status_code;
}m;
#endif