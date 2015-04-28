#include <common.h>
#include <libft.h>

int
main(void)
{
	char		*buf;

	get_next_line(0, &buf);
	printf("%s\n", buf);
	return (0);
}

// int
// main(void)
// {
// 	SOCKET			sock;
// 	SOCKADDR_IN 	sin;
// 	int				sock_err;
// 	socklen_t		recsize = sizeof(sin);
// 	char			buf[BUF_SIZE];
// 	int				n;

// 	/* Création de la socket */
// 	sock = socket(AF_INET, SOCK_STREAM, 0);

// 	/* Configuration de la connexion */
// 	sin.sin_addr.s_addr = inet_addr("127.0.0.1");
// 	sin.sin_family = AF_INET;
// 	sin.sin_port = htons(PORT);

// 	sock_err = connect(sock, (SOCKADDR*)&sin, recsize);
// 	if(sock_err != -1)
// 	{
// 		printf("Connexion à %s sur le port %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));

// 		n = recv(sock, buf, BUF_SIZE, 0);
// 		if (n > 0)
// 			printf("size : %d receive : %s\n", n, buf);

// 	}
// 	else
// 		perror("connect");

// 	/* On ferme la socket précédemment ouverte */
// 	close(sock);
 
// 	return (0);
// }