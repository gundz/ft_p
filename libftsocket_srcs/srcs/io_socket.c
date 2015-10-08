/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_socket.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgundlac <fgundlac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/08 20:37:46 by fgundlac          #+#    #+#             */
/*   Updated: 2015/10/08 20:37:47 by fgundlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>

#include <libftsocket.h>

SOCKET				open_socket(void)
{
	SOCKET			sock;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		perror("Error opening socket");
	return (sock);
}

int					new_socket(t_socket *socket, const short sin_family, const in_addr_t sin_addr, const u_short sin_port)
{
	if (socket == NULL)
		return (-1);
	if ((socket->fd = open_socket()) == -1)
		return (-1);
	socket->addr.sin_family = sin_family;
	socket->addr.sin_addr.s_addr = sin_addr;
	socket->addr.sin_port = sin_port;
	socket->socklen = sizeof(socket->addr);
	return (0);
}

int						get_client(t_socket *serv, t_socket *cli)
{
	cli->socklen = sizeof(cli->addr);
	cli->fd = accept(serv->fd, (struct sockaddr *)&cli->addr, &(cli->socklen));
	if (cli->fd < 0)
	{
		perror("ERROR on accept");
		return (-1);
	}
	send_int32(cli->fd, MSG_CO_CONFIRM);
	return (0);
}
