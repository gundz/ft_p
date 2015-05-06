#include <libftsocket.h>
#include <libft.h>

#include <stdlib.h>

char *
rec_msg(SOCK socket)
{
	int		size;
	int		n;
	char	*msg;

	n = recv(socket, &size, sizeof(int), 0);
	if (n == -1)
	{
		perror("msg size");
		return (NULL);
	}
	if (!(msg = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	n = recv(socket, msg, size, 0);
	msg[n] = '\0';
	if (n == -1)
	{
		perror("msg");
		free(msg);
		return (NULL);
	}
	return (msg);
}

int
main(void)
{
	/* Socket et contexte d'adressage du serveur */
	SOCKADDR_IN		sin;
	SOCK			sock;
	socklen_t recsize = sizeof(sin);
	
	/* Socket et contexte d'adressage du client */
	SOCKADDR_IN		csin;
	SOCK			csock;
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
				printf("Wait until client connect on port: %d...\n\n", PORT);

				csock = accept(sock, (SOCKADDR*)&csin, &crecsize);

				printf("client connect on socket %d with %s:%d\n", csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));

				while (1)
				{
					char	*msg;

					if ((msg = rec_msg(csock)) != NULL)
					{
						ft_putstr("receive command : \"");
						ft_putstr(msg);
						ft_putstr("\"\n");
						/*		commands		*/
						if (ft_strcmp("exit", msg) == 0)
						{
							free(msg);
							break ;
						}
						free(msg);
					}
				}

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