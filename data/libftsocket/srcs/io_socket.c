#include <libftsocket.h>
#include <libft.h>

t_socket *
open_socket(void)
{
	t_socket	*sock;

	if (!(sock = (t_socket *)malloc(sizeof(t_socket))))
		return(NULL);
	sock->size = sizeof(sock->sin);
	sock->sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock->sock == -1)
	{
		perror("socket");
		free(sock);
		return (NULL);
	}
	return (sock);
}

void
close_socket(t_socket *socket)
{
	close(socket->sock);
	free(socket);
}