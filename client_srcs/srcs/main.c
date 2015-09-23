#include <errno.h>
#include <stdio.h>

#include <libft.h>
#include <libftsocket.h>
#include <client.h>

int						main_client(char *addr, const int portno)
{
	t_socket			serv;

	if (init_client(addr, portno, &serv) == -1)
		return (EXIT_FAILURE);
	printf("%s: connected\n", inet_ntoa(serv.addr.sin_addr));

	send_file(serv.fd, "/mnt/FCB83109B830C3C4/tmp/test.exe");

	printf("%s: disconnected\n", inet_ntoa(serv.addr.sin_addr));
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
