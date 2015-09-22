
#include <socket.h>

int
main(void)
{
	int					portno = 5001;
	t_socket			serv;
	t_socket			cli;

	if (new_socket(&serv, AF_INET, INADDR_ANY, htons(portno)) == -1)
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

	return (0);
}