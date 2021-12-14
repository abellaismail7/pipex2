/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-bel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 11:52:05 by iait-bel          #+#    #+#             */
/*   Updated: 2021/12/12 11:52:05 by iait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STR_H
# define FT_STR_H

int				ft_strlen(char *str);
int				ft_strncmp(char *s1, char *s2, int n);
unsigned int	ft_strlcpy(char *dest, const char *src, unsigned int size);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strdup(char *src);
void			ft_putstrfd(int fd, char *str);
char			**ft_split(char *str, char c);
int				free_split(char **result);
int				show_error(char *basename, char* msg, int val);

#endif
