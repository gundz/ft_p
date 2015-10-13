/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uint32.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgundlac <fgundlac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/08 20:38:00 by fgundlac          #+#    #+#             */
/*   Updated: 2015/10/08 20:38:01 by fgundlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <libftsocket.h>

int					send_int32(int fd, int32_t var)
{
	if (send(fd, &var, sizeof(int32_t), 0) == -1)
		return (-1);
	return (0);
}

int					get_int32(int fd)
{
	int32_t			var;

	recv(fd, &var, sizeof(int32_t), 0);
	return (var);
}
