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

t_list *
store_file(const char *path, t_file_data *file_data)
{
	int			fd;
	char		buf[BUF_SIZE + 1];
	t_list		*file;
	int			n;
	int			nb_block;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		perror("");
	file = NULL;
	nb_block = 0;
	while ((n = read(fd, &buf, BUF_SIZE)))
	{
		buf[n] = '\0';
		lst_push_back(&file, ft_strdup(buf));
		nb_block++;
	}
	close(fd);
	file_data->size = lst_csize(file);
	file_data->block_size = BUF_SIZE;
	file_data->nb_block = nb_block;
	return (file);
}

SOCK_ERR
send_struct(t_socket *sock, void *struc, int size)
{
	SOCK_ERR			sock_err;
	char				*super = struc;

	sock_err = send(sock->sock, &(*super), size, 0);
	if (sock_err == -1)
		perror("send struct");
	return (sock_err);
}

void
send_file(t_socket *sock, const char *path)
{
	t_list			*file;
	t_file_data		file_data;
	t_list			*lstwalker;

	file = store_file(path, &file_data);
	send_struct(sock, &file_data, sizeof(t_file_data));
	lstwalker = file;
	while (lstwalker != NULL)
	{
		send_msg(sock->sock, (char *)lstwalker->data);
		if (lstwalker->next == NULL)
			break ;
		lstwalker = lstwalker->next;
	}
	lst_free(&file, 1);
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
			send_file(csock, "Makefile");
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