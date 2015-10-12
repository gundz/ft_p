/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgundlac <fgundlac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/08 20:37:53 by fgundlac          #+#    #+#             */
/*   Updated: 2015/10/08 20:37:54 by fgundlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftsocket.h>
#include <fcntl.h>
#include <stdio.h>

int						open_file_read(char *path)
{
	int					fd;

	if ((fd = open(path, O_RDONLY)) == -1)
	{
		return (-1);
	}
	return (fd);
}

int						open_file_write(char *path)
{
	int					fd;

	if ((fd = open(path, O_WRONLY | O_CREAT, 0644)) == -1)
	{
		return (-1);
	}
	return (fd);
}
