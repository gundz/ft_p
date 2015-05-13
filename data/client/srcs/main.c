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

typedef struct s_file_data
{
	uint32_t	size;
	uint32_t	block_size;
	uint32_t	nb_block;
}				t_file_data;

typedef struct	s_file
{
	uint32_t	block_id;
	char		*block;
}				t_file;

t_list *
rec_file_data(t_socket *sock, t_file_data *file_data)
{
	char			buf[file_data->block_size + 1];
	t_list			*file;
	int				n;
	unsigned int	i;
	int				size;

	file = NULL;
	i = 0;
	while (i < file_data->nb_block)
	{
		printf("%d%%\n", (i * file_data->block_size) * 100 / file_data->size);
		n = recv(sock->sock, &size, sizeof(int), 0);
		if (n == -1)
		{
			perror("rec_file_data size");
			return (NULL);
		}
		n = recv(sock->sock, &buf, size, 0);
		if (n == -1)
		{
			perror("rec_file_data data");
			return (NULL);
		}
		buf[n] = '\0';
		lst_push_back(&file, ft_strdup(buf));
		i++;
	}
	return (file);
}

t_list *
rec_file(t_socket *sock)
{
	t_file_data		file_data;
	t_list			*file;
	int				n;

	n = recv(sock->sock, &file_data, sizeof(t_file_data), 0);
	if (n == -1)
	{
		perror("receive file_data");
		return (NULL);
	}
	printf("size = %d | block_size = %d | nb_block = %d\n", file_data.size, file_data.block_size, file_data.nb_block);
	file = rec_file_data(sock, &file_data);

	t_list			*lstwalker;
	lstwalker = file;
	while (lstwalker != NULL)
	{
		printf("%s", (char *)lstwalker->data);
		if (lstwalker->next == NULL)
			break ;
		lstwalker = lstwalker->next;
	}
	lst_free(&file, 1);
	return (file);
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
			if (ft_strcmp(input, "get") == 0)
			{
				rec_file(sock);
			}

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