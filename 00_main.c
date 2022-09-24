/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 09:53:29 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/24 12:46:57 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
Mac leakcheck:
leaks -atExit -- ./pipex file1 "cmd1" "cmd2" file2
*/
int	main(int argc, char **argv, char **env)
{
	t_envl		e;

	setup(&e, argc, argv, env);
	if (e.here_doc)
		here_doc(&e);
	e.i = 0;
	firstchild(&e, e.i);
	e.i++;
	while (e.i < argc - e.n)
	{
		middlechild(&e, e.i);
		e.i++;
	}
	lastchild(&e, e.i);
	cleanup(&e);
	return (0);
}
