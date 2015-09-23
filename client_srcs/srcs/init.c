#include <libftsocket.h>

int					init_client(char *addr, const int portno, t_socket *serv)
{
	if (new_socket(serv, AF_INET, inet_addr(addr), htons(portno)) == -1)
		return (-1);
	if (connect(serv->fd, (struct sockaddr *)&serv->addr, serv->socklen) < 0)
	{
		perror("Error connecting 1");
		return (-1);
	}
	return (0);
}