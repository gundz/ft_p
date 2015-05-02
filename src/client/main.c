#include <common.h>
#include <libft.h>

int
main(void)
{
	SOCKET			sock;
	SOCKADDR_IN 	sin;
	int				sock_err;
	socklen_t		recsize = sizeof(sin);

	/* Création de la socket */
	sock = socket(AF_INET, SOCK_STREAM, 0);

	/* Configuration de la connexion */
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);

	sock_err = connect(sock, (SOCKADDR*)&sin, recsize);
	if(sock_err != -1)
	{
		printf("Connexion à %s sur le port %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));

		while (1)
		{
			char	*buf;

			ft_putstr("$>: ");
			get_next_line(0, &buf);
			ft_putchar(10);
			
			int size = ft_strlen(buf) + 1;
			sock_err = send(sock, &size, sizeof(int), 0);
			if (sock_err == -1)
				perror("transmission size");
			sock_err = send(sock, &(*buf), size, 0);
			if (sock_err == -1)
				perror("transmission");
			if (ft_strcmp(buf, "exit") == 0)
				break ;
		}
		shutdown(sock, 2);
	}
	else
		perror("connect");

	/* On ferme la socket précédemment ouverte */
	close(sock);
 
	return (0);
}