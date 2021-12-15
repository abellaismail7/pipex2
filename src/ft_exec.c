/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-bel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 13:13:18 by iait-bel          #+#    #+#             */
/*   Updated: 2021/12/12 18:22:36 by iait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "ft_str.h"
#include "pipex.h"
#include <fcntl.h>

int	_exec(t_data *data, int index)
{
	int		pid;
	char	**args;
	char	*file;

	pid = fork();
	if (pid == 0)
	{
		args = ft_split(data->cmds[index], ' ');
		if (args == NULL)
			exit(1);
		file = get_cmd_path(args[0], data->paths);
		if (file == NULL && ft_free(args))
			exit(127);
		execve(file, args, data->env);
		free_split(args);
		free(file);
		exit(0);
	}
	return (pid);
}

int	file2stdin(t_data *data, int fd)
{
	int	res;

	res = setupinput(data);
	ft_dup2(fd, STDOUT_FILENO);
	if (res == -1)
		return (-1);
	return (_exec(data, 0));
}

int	streamexec(t_data *data, int *pids, int fd_in)
{
	int	i;
	int	fdi;
	int	*fds;

	fds = malloc(sizeof(int) * (data->size - 2));
	if (fds == NULL)
		return (-1);
	i = 1;
	fdi = 0;
	while (i < data->size - 1)
	{
		assign_stdin(i, fd_in, fds[fdi - 2]);
		if (pipe(fds + fdi) == -1 && ft_free(fds))
			return (-1);
		ft_dup2(fds[fdi + 1], STDOUT_FILENO);
		pids[i] = _exec(data, i);
		fd_in = fds[fdi];
		if (i + 2 == data->size)
			break ;
		fdi += 2;
		i++;
	}
	free(fds);
	return (fd_in);
}

int	stdout2file(t_data *data, int readend)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_TRUNC | O_CREAT;
	if (data->until != NULL)
	{
		flags |= O_APPEND;
		flags &= ~O_TRUNC;
	}
	fd = open(data->file_out, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		close(readend);
		show_errno(data->execname, data->file_out);
		return (-1);
	}
	ft_dup2(readend, STDIN_FILENO);
	ft_dup2(fd, STDOUT_FILENO);
	return (_exec(data, data->size -1));
}

int	ft_exec(t_data *data)
{
	int	*pids;
	int	fildes[2];
	int	fd;
	int	status;

	if (pipe(fildes) == -1)
		return (1);
	pids = ft_ialloc(data->size, -1);
	if (pids == NULL)
		return (1);
	pids[0] = file2stdin(data, fildes[1]);
	fd = streamexec(data, pids, fildes[0]);
	if (fd == -1)
	{
		free(pids);
		return (1);
	}
	pids[data->size - 1] = stdout2file(data, fd);
	status = get_statuscode(data, pids);
	free(pids);
	return (status);
}
