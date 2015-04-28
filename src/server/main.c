#include <common.h>

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
		printf("Openned : %d\n", sock);

        /* Configuration */
        sin.sin_addr.s_addr = htonl(INADDR_ANY);  /* Adresse IP automatique */
        sin.sin_family = AF_INET;                 /* Protocole familial (IP) */
        sin.sin_port = htons(PORT);               /* Listage du port */
        sock_err = bind(sock, (SOCKADDR*)&sin, recsize);

        if (sock_err != -1)
        {
        	sock_err = listen(sock, 5);
        	printf("listen on port %d\n", PORT);

        	if (sock_err != -1)
        	{
                /* Attente pendant laquelle le client se connecte */
                printf("Patientez pendant que le client se connecte sur le port %d...\n", PORT);

                csock = accept(sock, (SOCKADDR*)&csin, &crecsize);

                printf("Un client se connecte avec la socket %d de %s:%d\n", csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));
        	}
        	else
        		perror("listen");
        }
        else
        	perror("bind");

        close(csock);
        printf("client socket closed\n");
		close(sock);
		printf("server closed");
	}
	else
		perror("socket");
	return (0);
}