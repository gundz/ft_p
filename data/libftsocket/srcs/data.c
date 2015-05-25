#include <libftsocket.h>

SOCK_ERR
send_data(t_socket *sock, void *data, int size)
{
	SOCK_ERR	sock_err;
	char		*tmp;

	tmp = data;
	sock_err = 0;
	if (size > 0)
	{
		sock_err = send(sock->sock, &size, sizeof(int), 0);
		if (sock_err == -1)
			perror("send_data size");
		sock_err = send(sock->sock, &(*tmp), size, 0);
		if (sock_err == -1)
			perror("send_data data");
	}
	return (sock_err);
}

int
rec_data(t_socket *sock, char *data)
{
	int		size;
	int		n;

	size = 0;
	n = recv(sock->sock, &size, sizeof(int), 0);
	if (n == -1)
	{
		perror("msg size");
		return (-1);
	}
	n = recv(sock->sock, data, size, 0);
	if (n == -1)
	{
		perror("msg");
		return (-1);
	}
	return (n);
}