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