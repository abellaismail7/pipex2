/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-bel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 11:34:50 by iait-bel          #+#    #+#             */
/*   Updated: 2021/12/12 11:34:50 by iait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define HEREDOC "here_doc"
# define HEREDOC_LEN 8

typedef struct s_data
{
	int		size;
	char	*until;
	char	*execname;
	char	*file_in;
	char	*file_out;
	char	**cmds;
	char	**paths;
	char	**env;
}	t_data;

void	setupinput(t_data *data);
void	die(char *basename, char *file);
char	*get_cmd_path(char *cmd, char **paths);
char	**get_paths(char **env);
int		show_errno(char *basename, char *filename);
int		ft_free(void *free);
int		*ft_ialloc(int size, int defval);
int		ft_dup2(int fd1, int fd2);
int		ft_exec(t_data *data);
int		get_statuscode(t_data *data, int *pids);

#endif
