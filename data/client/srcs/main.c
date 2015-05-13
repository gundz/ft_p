#include <libftsocket.h>
#include <libft.h>

/*
CLIENT : INPUT COMMANDE
SERVEUR : check commande à partir d'une fonction
qui checke dans une liste pour le message et attribue une fonction à 
partir d'un pointeur sur fonction
renvois un success ou error au client
et le serveur renvois le code correspondant à l'échange en cour (début transfert etc...)
et l'échange commence

amélioration : codes dans un fichier sous forme "code- message" (cf rfc 959)
structure qui contient code + message + accès à partir d'une fonction

serveur
{
	msg = get_msg()
	ret = check_msg(msg)
	if (ret == OK)
	{
		send_msg(ok)
		get_function(ret);
	}
}

client
{
	send_msg()
	ret = get_msg()
	if (ret == OK)
	{
		get_function()
	}
}
*/

t_socket *
connect_client(const char *addr)
{
	t_socket		*sock;
	SOCK_ERR		sock_err;

	if ((sock = open_socket()) == NULL)
		return (sock);

	/* Configuration de la connexion */
	sock->sin.sin_addr.s_addr = inet_addr(addr);
	sock->sin.sin_family = AF_INET;
	sock->sin.sin_port = htons(PORT);

	sock_err = connect(sock->sock, (SOCKADDR*)&sock->sin, sock->size);
	if (sock_err == -1)
	{
		perror("connect");
		return (sock);
	}
	printf("Connexion à %s sur le port %d\n", inet_ntoa(sock->sin.sin_addr), htons(sock->sin.sin_port));
	return (sock);
}

int
main(void)
{
	t_socket	*sock;
	char		*input;

	sock = connect_client("127.0.0.1");
	if (sock == NULL)
		return (-1);
	while (1)
	{
		input = NULL;
		if (send_msg_input(sock->sock, &input) != -1)
		{
			if (ft_strcmp(input, "exit") == 0)
			{
				free(input);
				break ;
			}
			free(input);
		}
	}
	shutdown(sock->sock, 2);
	close_socket(sock);
	return (0);
}