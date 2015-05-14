#include <libftsocket.h>
#include <libft.h>
#include <server.h>

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

#define BUF_SIZE 32
#include <fcntl.h>

SOCK_ERR
send_struct(t_socket *sock, void *struc, int size)
{
	SOCK_ERR			sock_err;
	char				*tmp;

	tmp = struc;
	sock_err = send(sock->sock, &(*tmp), size, 0);
	if (sock_err == -1)
		perror("send struct");
	return (sock_err);
}

void
get_file_data(const int fd, t_file_data *file_data)
{
	char		buf[BUF_SIZE + 1];
	int			n;
	int			size;
	int			nb_block;

	size = 0;
	nb_block = 0;
	while ((n = read(fd, &buf, BUF_SIZE)))
	{
		size += n;
		nb_block++;
	}
	file_data->size = size;
	file_data->nb_block = nb_block;
	file_data->block_size = BUF_SIZE;
	lseek(fd, -size, SEEK_CUR);
}

SOCK_ERR
send_data(t_socket *sock, void *data, int size)
{
	SOCK_ERR	sock_err;
	char		*tmp;

	tmp = data;
	sock_err = 0;
	if (size > 0)
	{
		sock_err = send(sock->sock, &size, sizeof(int), 0);
		if (sock_err == -1)
			perror("send_data size");
		sock_err = send(sock->sock, &(*tmp), size, 0);
		if (sock_err == -1)
			perror("send_data data");
	}
	return (sock_err);
}

void
send_file(t_socket *sock, const char *path)
{
	int				fd;
	t_file_data		file_data;
	int				n;
	char			buf[BUF_SIZE + 1];

	fd = open(path, O_RDONLY);
	get_file_data(fd, &file_data);
	send_struct(sock, &file_data, sizeof(t_file_data));
	printf("send file : %s\n", path);
	printf("size = %d | block_size = %d | nb_block = %d\n", file_data.size, file_data.block_size, file_data.nb_block);
	while ((n = read(fd, &buf, BUF_SIZE)))
	{
		buf[n] = '\0';
		printf("%s", buf);
		send_data(sock, buf, n);
	}
	close(fd);
}

void
talk(t_socket *csock, int *run, int *connected)
{
	char	*msg;

	if ((msg = rec_msg(csock->sock)) != NULL)
	{
		printf("receive command : \"%s\"\n", msg);

		if (ft_strcmp("get", msg) == 0)
		{
			send_file(csock, "client");
		}

		if (ft_strcmp("ls", msg) == 0)
		{
			send_ls(csock, "./");
		}

		if (ft_strcmp("exit", msg) == 0)
		{
			*connected = 0;
			free(msg);
			return ;
		}
		if (ft_strcmp("shutdown", msg) == 0)
		{
			free(msg);
			*connected = 0;
			*run = 0;
			return ;
		}

		// if (check_command(msg) == 0)
		// {
		// 	send_msg(csock, "200- OK");
		// }
		free(msg);
	}
}

int
main(void)
{
	t_socket		*ssock;
	t_socket		*csock;
	int				run;
	int				connected;

	ssock = new_server_socket();
	if (ssock == NULL)
		return (-1);

	if (bind_and_listen(ssock) == -1)
	{
		close(ssock->sock);
		return (-1);
	}

	run = 1;
	while (run == 1)
	{
		connected = 1;
		csock = wait_for_client(ssock);
		while (connected == 1)
		{
			talk(csock, &run, &connected);
		}
		close_socket(csock);
		printf("client socket closed\n\n");
	}

	close_socket(ssock);
	printf("server closed\n");
	return (0);
}