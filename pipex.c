/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbiederm <pbiederm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 15:54:53 by pbiederm          #+#    #+#             */
/*   Updated: 2022/07/31 15:54:53 by pbiederm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// needs to stay in lines and have the error handling taken care of
#include "pipex.h"

char	**ft_path_array(char **env)
{
	int		i;
	char	**path_array;

	path_array = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] ==
		'T' && env[i][3] == 'H' && env[i][4] == '=')
		{
			path_array = ft_split(ft_substr(env[i], 5, ft_strlen(env[i])), ':');
			break ;
		}
		i++;
	}
	path_array[i] = NULL;
	return (path_array);
}

int	ft_child_one(int *fd, int *pfd, char **av, char **env)
{
	close(pfd[0]);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(pfd[1], STDOUT_FILENO);
	close(pfd[1]);
	m.i = 0;
	m.p = ft_path_array(env);
	m.c = ft_split(av[2], ' ');
	if (m.c[0] == NULL)
	{
		perror("Enter the first command (infile cmd1 cmd2 outfile)");
		exit(666);
	}
	m.a_c = -1;
	while (m.p[m.i] != NULL)
	{
		m.a_c = access(ft_strjoin(m.p[m.i], ft_strjoin("/", m.c[0])), F_OK);
		if (m.a_c == 0)
			execve(ft_strjoin(m.p[m.i], ft_strjoin("/", m.c[0])), m.c, env);
		m.i++;
	}
	perror("Enter a valid first command (infile cmd1 cmd2 outfile)");
	exit(667);
}

void	ft_child_two(int *fd, int *pfd, char **av, char **env)
{
	close(pfd[1]);
	close(fd[0]);
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	m.i = 0;
	m.p = ft_path_array(env);
	m.c = ft_split(av[3], ' ');
	if (m.c[0] == NULL)
	{
		perror("Enter the second command (infile cmd1 cmd2 outfile)");
		exit (668);
	}
	while (m.p[m.i] != NULL)
	{
		if (access(ft_strjoin(m.p[m.i], ft_strjoin("/", m.c[0])), F_OK) == 0)
			execve(ft_strjoin(m.p[m.i], ft_strjoin("/", m.c[0])), m.c, env);
		m.i++;
	}
	perror("Enter a valid second command (infile cmd1 cmd2 outfile)");
	exit (670);
}

void	parent(int *fd, int *pfd, int id_greg, int id_sara)
{
	close(fd[0]);
	close(fd[1]);
	close(pfd[1]);
	close(pfd[0]);
	waitpid(id_greg, &m.status, 0);
	waitpid(id_sara, &m.status, 0);
	free(m.p);
	free(m.c);
	if (WIFEXITED(m.status))
	{
		m.status_code = WEXITSTATUS(m.status);
		if (m.status_code != 0)
		{
			perror("Wrong exit");
			exit(m.status_code);
		}
	}
	exit(0);
}

int	main(int ac, char **av, char **env)
{
	if (ac == 5)
	{
		m.fd[0] = open(av[1], O_RDONLY);
		if (m.fd[0] < 0)
			ft_err_infile();
		m.fd[1] = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
		if (pipe(m.pfd) == -1)
			ft_err_pipe();
		m.id_greg = fork();
		if (m.id_greg == -1)
			ft_err_pipe();
		if (m.id_greg == 0)
			ft_child_one(m.fd, m.pfd, av, env);
		else
		{
			m.id_sara = fork();
			if (m.id_sara == 0)
				ft_child_two(m.fd, m.pfd, av, env);
			else
				parent(m.fd, m.pfd, m.id_greg, m.id_sara);
		}
	}
	else
		ft_err_ac();
}
