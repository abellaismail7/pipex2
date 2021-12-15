/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-bel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 19:48:03 by iait-bel          #+#    #+#             */
/*   Updated: 2021/12/12 19:48:03 by iait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "pipex.h"
#include "ft_str.h"

void	ft_putstr(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
}

void	assign_stdin(int i, int fd_in, int fdlast_in)
{
	if (i == 1)
		ft_dup2(fd_in, STDIN_FILENO);
	else
		ft_dup2(fdlast_in, STDIN_FILENO);
}

int	readfromkeyboard(char *until)
{
	int		fildes[2];
	int		u_len;
	int		n;
	char	*buf;

	u_len = ft_strlen(until);
	if (pipe(fildes) == -1)
		return (-1);
	buf = malloc(sizeof(char *) * (u_len + 1));
	if (buf == NULL)
		return (-1);
	ft_putstr(1, "heredoc> ");
	while (1)
	{
		n = read(STDIN_FILENO, buf, u_len);
		if (n == -1 || (n == u_len && ft_strncmp(buf, until, n) == 0))
			break ;
		write(fildes[1], buf, n);
		if (n != 0 && buf[n - 1] == '\n')
			ft_putstr(1, "heredoc> ");
	}
	free(buf);
	close(fildes[1]);
	return (fildes[0]);
}

void	fake_input(int is_heredoc)
{
	int	fildes[2];

	if (is_heredoc || pipe(fildes) == -1)
		return ;
	ft_dup2(fildes[0], STDIN_FILENO);
	close(fildes[1]);
}

int	setupinput(t_data *data)
{
	int	fd_in;

	if (data->until != NULL)
		fd_in = readfromkeyboard(data->until);
	else
		fd_in = open(data->file_in, O_RDONLY);
	if (fd_in == -1)
	{
		show_errno(data->execname, data->file_in);
		fake_input(data->until != NULL);
	}
	else
		ft_dup2(fd_in, STDIN_FILENO);
	return (fd_in);
}
