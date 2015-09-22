#include <string.h>

#include <socket.h>

int
main(void)
{	
	int					portno = 5001;
	t_socket			serv;

	if (new_socket(&serv, AF_INET, inet_addr("127.0.0.1"), htons(portno)) == -1)
		return (EXIT_FAILURE);

	if (connect(serv.fd, (struct sockaddr *)&serv.addr, serv.socklen) < 0)
		perror("Error connecting 1");

	send_msg_type(serv.fd, UINT32);

	close(serv.fd);

	return (0);
}