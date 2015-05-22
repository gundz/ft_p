#include <libftsocket.h>
#include <libft.h>
#include <server.h>

#define BUF_SIZE 4096
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
#include <sys/stat.h>
#include <math.h>
void
get_file_data(const int fd, char *filename, t_file_data *file_data)
{
	struct stat		buf;
	int				i;

	fstat(fd, &buf);
	//check fstat output
	i = 0;
	while (filename[i] != '\0')
	{
		file_data->filename[i] = filename[i];
		i++;
	}
	file_data->filesize = (int)buf.st_size;
	file_data->block_size = BUF_SIZE;
	file_data->nb_block = (int)ceil(buf.st_size / BUF_SIZE);
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
send_file(t_socket *sock, char *path)
{
	int				fd;
	t_file_data		file_data;
	int				n;
	char			buf[BUF_SIZE + 1];

	fd = open(path, O_RDONLY);
	get_file_data(fd, path, &file_data);
	send_struct(sock, &file_data, sizeof(t_file_data));
	printf("send file : %s\n", path);
	printf("size = %d | block_size = %d | nb_block = %d\n", file_data.filesize, file_data.block_size, file_data.nb_block);
	while ((n = read(fd, &buf, BUF_SIZE)))
	{
		buf[n] = '\0';
		send_data(sock, buf, n);
	}
	printf("file sended !\n");
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
			send_file(csock, "test.mp3");
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