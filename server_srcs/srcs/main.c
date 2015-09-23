#include <errno.h>
#include <stdio.h>

#include <libft.h>
#include <libftsocket.h>
#include <server.h>

int						get_client(t_socket *serv)
{
	t_socket			cli;

	cli.socklen = sizeof(cli.addr);
	cli.fd = accept(serv->fd, (struct sockaddr *)&cli.addr, &(cli.socklen));
	if (cli.fd < 0)
	{
		perror("ERROR on accept");
		return (-1);
	}
	printf("%s: connected\n", inet_ntoa(cli.addr.sin_addr));


	get_file(cli.fd);


	close(cli.fd);
	printf("%s: disconnected\n", inet_ntoa(cli.addr.sin_addr));
	return (0);
}

int						main_server(const int portno)
{
	t_socket			serv;

	if (init_server(portno, &serv) == -1)
		return (EXIT_FAILURE);

	if (get_client(&serv) == -1)
		return (EXIT_FAILURE);

	close(serv.fd);
	return (EXIT_SUCCESS);	
}

int						main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: ./server port\n");
		return (EXIT_FAILURE);
	}
	return (main_server(ft_atoi(argv[1])));
}
