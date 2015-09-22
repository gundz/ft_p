#include <libft.h>
#include <libftsocket.h>

int						main_server(const int portno)
{
	t_socket			serv;
	t_socket			cli;

	if (new_socket(&serv, AF_INET, INADDR_ANY, htons(portno)) == -1)
		return (EXIT_FAILURE);

	int yes = 1;
	if(setsockopt(serv.fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) 
		return (EXIT_FAILURE);

	if (bind(serv.fd, (struct sockaddr *)&serv.addr, serv.socklen) == -1)
		perror("Error on binding");

	listen(serv.fd, 5);

	cli.socklen = sizeof(cli.addr);
	cli.fd = accept(serv.fd, (struct sockaddr *)&cli.addr, &(cli.socklen));
	if (cli.fd < 0)
		perror("ERROR on accept");

	printf("%s: connected\n", inet_ntoa(cli.addr.sin_addr));

	t_msg_type				type;

	type = get_msg_type(cli.fd);
	if (type == MSG)
		printf("MSG\n");
	else
		printf("None\n");

	close(cli.fd);

	printf("%s: disconnected\n", inet_ntoa(cli.addr.sin_addr));

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
