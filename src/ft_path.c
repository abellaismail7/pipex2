/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-bel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 13:01:13 by iait-bel          #+#    #+#             */
/*   Updated: 2021/12/12 13:01:13 by iait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"
#include "pipex.h"
#include <unistd.h>
#include <stdlib.h>

char	**get_paths(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (ft_split(env[i] + 5, ':'));
		i++;
	}
	return (0);
}

char	*check_relativepath(char *cmd)
{
	int	res;

	res = access(cmd, F_OK | X_OK);
	if (res == -1)
		show_errno("pipex", cmd);
	if (res == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

char	*check_envpath(char *cmd, char **paths)
{
	char	*filename;
	int		i;

	i = 0;
	filename = NULL;
	if (paths == NULL)
		return (NULL);
	while (paths[i])
	{
		filename = ft_strjoin(paths[i], cmd);
		if (filename != NULL && access(filename, F_OK | X_OK) == 0)
			break ;
		free(filename);
		filename = NULL;
		i++;
	}
	return (filename);
}

char	*get_cmd_path(char *cmd, char **paths)
{
	char	*filename;

	if (cmd[0] == '.')
	{
		filename = check_relativepath(cmd);
	}
	else
	{
		filename = check_envpath(cmd, paths);
		if (filename == NULL)
		{
			ft_putstrfd(2, "pipex: command not found: ");
			ft_putstrfd(2, cmd);
			ft_putstrfd(2, "\n");
		}
	}
	return (filename);
}
