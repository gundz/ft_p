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
		printf("%d%% | %d\n", (i * file_data->block_size) * 100 / file_data->size, i);
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

int
rec_data(t_socket *sock, char **data)
{
	int		size;
	int		n;

	n = recv(sock->sock, &size, sizeof(int), 0);
	if (n == -1)
	{
		perror("msg size");
		return (-1);
	}
	if (!(*data = (char *)malloc(sizeof(char) * size)))
		return (-1);
	n = recv(sock->sock, *data, size, 0);
	if (n == -1)
	{
		perror("msg");
		free(*data);
		return (-1);
	}
	return (size);
}

#include <fcntl.h>
void
rec_file(t_socket *sock)
{
	t_file_data		file_data;

	recv(sock->sock, &file_data, sizeof(t_file_data), 0);
	printf("size = %d | block_size = %d | nb_block = %d\n", file_data.size, file_data.block_size, file_data.nb_block);
	int			fd;
	char		*buf;
	int			size;
	unsigned int			i;
	fd = open("tmp.png", O_WRONLY | O_CREAT);

	i = 0;
	while (i != file_data.nb_block)
	{
		printf("%d%%\n", (i * file_data.block_size) * 100 / file_data.size);
		size = rec_data(sock, &buf);
		write(fd, buf, size);
		free(buf);
		i++;
	}
	printf("100%%\n");
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