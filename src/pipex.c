/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-bel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:47:21 by iait-bel          #+#    #+#             */
/*   Updated: 2021/12/14 15:47:21 by iait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_str.h"
#include "pipex.h"

int	setupdata(t_data *data, int ac, char **av)
{
	int	is_heredoc;

	data->until = NULL;
	is_heredoc = (ft_strncmp(av[1], HEREDOC, HEREDOC_LEN) == 0);
	if (is_heredoc)
		data->until = av[2];
	data->execname = av[0];
	data->file_in = av[1];
	data->file_out = av[ac - 1];
	data->paths = get_paths(data->env);
	if (data->paths == NULL)
		return (-1);
	data->size = ac - 3 - is_heredoc;
	data->cmds = av + 2 + is_heredoc;
	return (0);
}

int	main(int ac, char *av[], char **env)
{
	t_data	data;
	int		status;

	if (ac < 5)
	{
		ft_putstrfd(2, av[0]);
		ft_putstrfd(2, ": Not Enough Arguments\n");
		exit(1);
	}
	data.env = env;
	status = setupdata(&data, ac, av);
	if (status == -1)
		exit(1);
	status = ft_exec(&data);
	free(data.paths);
	return (status);
}
