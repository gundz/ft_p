#include <libftsocket.h>
#include <sys/socket.h>

SOCK_ERR
send_struct(t_socket *sock, void *struc, int size)
{
	SOCK_ERR			sock_err;
	char				*tmp;

	tmp = struc;
	sock_err = send(sock->sock, &(*tmp), size, 0);
	if (sock_err == -1)
		perror("send struct");
	return (sock_err);
}