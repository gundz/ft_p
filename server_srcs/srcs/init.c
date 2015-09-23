#include <libftsocket.h>

int						init_server(const int portno, t_socket *serv)
{
	static int			yes = 1;

	if (new_socket(serv, AF_INET, INADDR_ANY, htons(portno)) == -1)
		return (-1);
	if(setsockopt(serv->fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) 
		return (-1);
	if (bind(serv->fd, (struct sockaddr *)&serv->addr, serv->socklen) == -1)
		perror("Error on binding");
	listen(serv->fd, 5);
	return (0);	
}