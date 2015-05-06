#include <libftsocket.h>

SOCK
open_socket(void)
{
	SOCK			sock;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		perror("socket");
	return (sock);
}