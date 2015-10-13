/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgundlac <fgundlac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/08 20:37:33 by fgundlac          #+#    #+#             */
/*   Updated: 2015/10/08 20:37:33 by fgundlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <libft.h>
#include <libftsocket.h>

int					send_char_string(int fd, char *msg)
{
	int				len;

	len = ft_strlen(msg);
	if (send_int32(fd, len) == -1)
		return (-1);
	if (send(fd, &(*msg), sizeof(char) * len, 0) != len)
	{
		printf("Error while sending char string");
		return (-1);
	}
	return (0);
}

char				*get_char_string(int fd)
{
	int32_t			len;
	char			*msg;
	int32_t			n;

	len = get_int32(fd);
	if (!(msg = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	n = 0;
	while ((n += recv(fd, &(*msg) + n, sizeof(char) * len, 0)) < len)
	{
	}
	msg[len] = '\0';
	return (msg);
}
