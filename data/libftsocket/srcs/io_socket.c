#include <libftsocket.h>

SOCKET
open_socket(void)
{
	SOCKET			sock;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		perror("socket");
	return (sock);
}