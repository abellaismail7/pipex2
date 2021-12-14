/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-bel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:13:46 by iait-bel          #+#    #+#             */
/*   Updated: 2021/12/12 18:13:46 by iait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include "ft_str.h"

int	show_errno(char *basename, char *filename)
{
	char	*str;

	if (errno)
	{
		str = strerror(errno);
		write(2, basename, ft_strlen(basename));
		write(2, ": ", 2);
		write(2, filename, ft_strlen(filename));
		write(2, ": ", 2);
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
		errno = 0;
		return (1);
	}
	return (0);
}
