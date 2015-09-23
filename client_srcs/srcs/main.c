#include <libft.h>
#include <libftsocket.h>
#include <client.h>

int						main_client(char *addr, const int portno)
{
	t_socket			serv;

	if (init_client(addr, portno, &serv) == -1)
		return (EXIT_FAILURE);

	send_msg(serv.fd, "test");

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
