#include <common.h>
#include <libft.h>

SOCKET
open_socket(void)
{
	SOCKET			sock;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		perror("socket");
	return (sock);
}

SOCKET
connect_client(const char *addr)
{
	SOCKET			sock;
	SOCKADDR_IN 	sin;
	socklen_t		recsize = sizeof(sin);
	SOCKET_ERR		sock_err;

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
	char	*buf;
	int		size;
	int		sock_err;
	SOCKET	sock;

	sock = connect_client("127.0.0.1");
	if (sock == -1)
		return (-1);
	while (1)
	{
		ft_putstr("$>: ");
		get_next_line(0, &buf);
		size = ft_strlen(buf);

		sock_err = send(sock, &size, sizeof(int), 0);
		if (sock_err == -1)
			perror("transmission size");
		
		sock_err = send(sock, &(*buf), size, 0);
		if (sock_err == -1)
			perror("transmission");
		
		if (ft_strcmp(buf, "exit") == 0)
			break ;

		free(buf);
	}
	shutdown(sock, 2);
	close(sock);
	return (0);
}