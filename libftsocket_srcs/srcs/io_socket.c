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

#include <stdio.h>
#include <libftsocket.h>

int					open_socket(void)
{
	int				sock;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		printf("Error while opening socket");
	return (sock);
}

int					new_socket(t_socket *socket, short sin_family, \
	in_addr_t sin_addr, u_short sin_port)
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

int					get_client(t_socket *serv, t_socket *cli)
{
	cli->socklen = sizeof(cli->addr);
	cli->fd = accept(serv->fd, (struct sockaddr *)&cli->addr, &(cli->socklen));
	if (cli->fd < 0)
	{
		printf("Error while acept\n");
		return (-1);
	}
	send_int32(cli->fd, MSG_CO_CONFIRM);
	return (0);
}

int					safe_recv(int sockfd, void *buf, int buf_size)
{
	int				i;

	i = recv(sockfd, buf, buf_size, 0);
	if (i <= 0)
		printf("Error: server disconected\n");
	return (i);
}
