#include <common.h>
#include <libft.h>

int
main(void)
{
	/* Socket et contexte d'adressage du serveur */
	SOCKADDR_IN		sin;
	SOCKET			sock;
	socklen_t recsize = sizeof(sin);
	
	/* Socket et contexte d'adressage du client */
	SOCKADDR_IN		csin;
	SOCKET			csock;
	socklen_t crecsize = sizeof(csin);
	
	int 			sock_err;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock != -1)
	{
		printf("Openned socket : %d\n", sock);

		/* Configuration */
		sin.sin_addr.s_addr = htonl(INADDR_ANY);  /* Adresse IP automatique */
		sin.sin_family = AF_INET;                 /* Protocole familial (IP) */
		sin.sin_port = htons(PORT);               /* Listage du port */

		int yes = 1;
		if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
			perror("setsockopt");

		sock_err = bind(sock, (SOCKADDR*)&sin, recsize);

		if (sock_err != -1)
		{
			sock_err = listen(sock, 5);
			printf("listen on port %d\n", PORT);

			if (sock_err != -1)
			{
				/* Attente pendant laquelle le client se connecte */
				printf("Wait until client connect on port: %d...\n\n", PORT);

				csock = accept(sock, (SOCKADDR*)&csin, &crecsize);

				printf("client connect on socket %d with %s:%d\n", csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));

				char			buf[BUF_SIZE];
				int				n;
				// while (1)
				// {
					n = recv(csock, buf, BUF_SIZE, 0);
					buf[n] = '\0';
					// if (ft_strcmp("exit", buf) == 0)
						// break ;
					if (n > 0)
						printf("size : %d receive : %s\n", n, buf);
				// }

				close(csock);
				printf("client socket closed\n\n");
			}
			else
				perror("listen");
			close(sock);
			printf("server closed\n");
		}
		else
			perror("bind");
	}
	else
		perror("socket");
	return (0);
}