#include <libftsocket.h>

t_socket *
new_server_socket(void)
{
	t_socket	*sock;

	sock = open_socket();
	if (sock->sock != -1)
	{
		printf("Openned server socket : %d\n", sock->sock);
		/* Configuration */
		sock->sin.sin_addr.s_addr = htonl(INADDR_ANY);  /* Adresse IP automatique */
		sock->sin.sin_family = AF_INET;                 /* Protocole familial (IP) */
		sock->sin.sin_port = htons(PORT);               /* Listage du port */
	}
	else
	{
		perror("server socket");
		free(sock);
		return (NULL);
	}
	return (sock);
}

int
bind_and_listen(t_socket *ssock)
{
	static int			yes = 1;
	int					sock_err;


	if(setsockopt(ssock->sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
		perror("setsockopt");

	sock_err = bind(ssock->sock, (SOCKADDR*)&ssock->sin, ssock->size);
	if (sock_err == -1)
	{
		perror("bind");
		return (sock_err);
	}

	sock_err = listen(ssock->sock, 5);
	if (sock_err == -1)
	{
		perror("listen");
		return (sock_err);
	}
	printf("listen on port %d\n", PORT);
	return (0);
}

t_socket *
wait_for_client(t_socket *ssock)
{
	t_socket		*csock;

	csock = open_socket();
	printf("Wait until client connect on port: %d...\n\n", PORT);
	csock->sock = accept(ssock->sock, (SOCKADDR*)&csock->sin, &csock->size);
	printf("client connect on socket %d with %s:%d\n", csock->sock, inet_ntoa(csock->sin.sin_addr), htons(csock->sin.sin_port));
	return (csock);
}