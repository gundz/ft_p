/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgundlac <fgundlac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/08 20:37:36 by fgundlac          #+#    #+#             */
/*   Updated: 2015/10/08 20:37:37 by fgundlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <stdio.h>
#include <libftsocket.h>

int					get_file(int sockfd, int fd, void (*f)(off_t, off_t))
{
	struct stat		s;
	char			buf[BUFSIZ];
	off_t			i;
	off_t			j;

	if (safe_recv(sockfd, &s, sizeof(struct stat)) <= 0)
		return (-1);
	i = 0;
	while (i < s.st_size)
	{
		if ((j = recv(sockfd, &buf, BUFSIZ, 0)) <= 0)
			return (-1);
		write(fd, buf, j);
		if (f)
			f(i, s.st_size);
		i += j;
	}
	if (f)
		f(i, s.st_size);
	return (0);
}
