/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-bel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:11:05 by iait-bel          #+#    #+#             */
/*   Updated: 2021/12/12 18:11:05 by iait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_str.h"
#include "pipex.h"

int	ft_dup2(int fd1, int fd2)
{
	int	res;
	
	res = dup2(fd1, fd2);
	if (res == -1)
	{
		show_errno("pipex", "");
		return res;
	}
	close(fd1);
	return (res);
}

int show_error(char *basename, char* msg, int val)
{
	ft_putstrfd(2, basename);
	ft_putstrfd(2, msg);
	ft_putstrfd(2, "\n");
	return val;
}

int	*ft_ialloc(int size, int defval)
{

	int	*mem;

	mem = (int *) malloc(sizeof(int) * size);
	while (size--)
	{
		mem[size] = defval;
	}
	return (mem);
}

int ft_free(void *ptr)
{
	free(ptr);
	return (1);
}
