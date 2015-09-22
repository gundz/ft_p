#ifndef		SOCKET_H
# define	SOCKET_H

# include <sys/socket.h>

# include <arpa/inet.h>

# include <unistd.h>

# include <stdio.h>
# include <errno.h>

# include <stdlib.h>

typedef int SOCKET;

typedef struct			s_socket
{
	SOCKET				fd;
	struct sockaddr_in	addr;
	socklen_t			socklen;
}						t_socket;

typedef enum			e_msg_type
{
	MSG, UINT32
}						t_msg_type;

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

int					send_msg_type(const int fd, const t_msg_type type)
{
	int				n;

	n = send(fd, &type, sizeof(type), MSG_CONFIRM);
	printf("%d\n", n);
	perror("send_msg_type");
	return (n);
}

t_msg_type			get_msg_type(const int fd)
{
	t_msg_type		type;

	recv(fd, &type, sizeof(type), 0);
	return (type);
}

#endif