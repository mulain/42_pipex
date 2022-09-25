/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 18:07:20 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/25 23:34:30 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	rotate_pipes(t_envl *e)
{
	int		*temp;

	temp = e->prev_pipe;
	e->prev_pipe = e->curr_pipe;
	e->curr_pipe = temp;
}

void	redirect_io(t_envl *e, int input, int output)
{
	if (dup2(input, STDIN_FILENO) == -1)
		error_msg_exit(e, "redirect input");
	close(input);
	if (dup2(output, STDOUT_FILENO) == -1)
		error_msg_exit(e, "redirect output");
	close(output);
}
