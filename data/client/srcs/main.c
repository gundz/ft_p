#include <libftsocket.h>
#include <libft.h>

SOCK
connect_client(const char *addr)
{
	SOCK			sock;
	SOCKADDR_IN 	sin;
	socklen_t		recsize = sizeof(sin);
	SOCK_ERR		sock_err;

	if ((sock = open_socket()) == -1)
		return (sock);

	/* Configuration de la connexion */
	sin.sin_addr.s_addr = inet_addr(addr);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);

	sock_err = connect(sock, (SOCKADDR*)&sin, recsize);
	if (sock_err == -1)
	{
		perror("connect");
		return (-1);
	}
	printf("Connexion à %s sur le port %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));
	return (sock);
}

SOCK_ERR
send_msg(SOCK socket, char *msg)
{
	SOCK_ERR	sock_err;
	int			size;

	sock_err = 0;
	size = ft_strlen(msg);
	if (size > 0)
	{
		sock_err = send(socket, &size, sizeof(int), 0);
		if (sock_err == -1)
			perror("send_msg size");
		sock_err = send(socket, &(*msg), size, 0);
		if (sock_err == -1)
			perror("send_msg");
	}
	return (sock_err);
}

SOCK_ERR
send_msg_input(SOCK socket, char **input)
{
	SOCK_ERR	sock_err;

	ft_putstr("$>: ");
	get_next_line(0, input);
	sock_err = send_msg(socket, *input);
	return (sock_err);
}

int
main(void)
{
	SOCK	sock;
	char	*input;

	sock = connect_client("127.0.0.1");
	if (sock == -1)
		return (-1);
	while (1)
	{
		input = NULL;
		if (send_msg_input(sock, &input) != -1)
		{
			if (ft_strcmp(input, "exit") == 0)
			{
				free(input);
				break ;
			}
			free(input);
		}
	}
	shutdown(sock, 2);
	close(sock);
	return (0);
}