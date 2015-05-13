#include <libftsocket.h>
#include <libft.h>

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
		close_socket(sock);
		return (NULL);
	}
	printf("Connexion à %s sur le port %d\n", inet_ntoa(sock->sin.sin_addr), htons(sock->sin.sin_port));
	return (sock);
}

void
receive_ls(t_socket *socket)
{
	uint32_t		size;
	t_list			*files;
	int				n;
	t_list			*lstwalker;

	n = recv(socket->sock, &size, sizeof(uint32_t), 0);
	if (n == -1)
	{
		perror("receive_ls size");
		return ;
	}
	files = NULL;
	while (size--)
		lst_push_back(&files, rec_msg(socket->sock));
	lstwalker = files;
	while (lstwalker != NULL)
	{
		printf("%s\n", (char *)lstwalker->data);
		if (lstwalker->next == NULL)
			break ;
		lstwalker = lstwalker->next;
	}
	lst_free(&files, 1);
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
			if (ft_strcmp(input, "ls") == 0)
			{
				receive_ls(sock);
			}
			if (ft_strcmp(input, "exit") == 0 || ft_strcmp(input, "shutdown") == 0)
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