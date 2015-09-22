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