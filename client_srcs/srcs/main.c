#include <libft.h>
#include <libftsocket.h>

int						main_client(char *addr, const int portno)
{
	t_socket			serv;

	if (new_socket(&serv, AF_INET, inet_addr(addr), htons(portno)) == -1)
		return (EXIT_FAILURE);

	if (connect(serv.fd, (struct sockaddr *)&serv.addr, serv.socklen) < 0)
		perror("Error connecting 1");

	send_msg_type(serv.fd, MSG);

	close(serv.fd);
	return (EXIT_SUCCESS);
}

int						main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("Usage: ./client addr port\n");
		return (EXIT_FAILURE);
	}
	return (main_client(argv[1], ft_atoi(argv[2])));
}
