/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 19:10:31 by wmardin           #+#    #+#             */
/*   Updated: 2022/09/25 19:11:53 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	char *knudel[2] = {"ls", "-l"};

	execve("ls", knudel , env);
}