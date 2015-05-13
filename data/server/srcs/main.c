#include <libftsocket.h>
#include <libft.h>
#include <server.h>

#include <dirent.h>

t_list *
list_dir(const char *path)
{
	DIR				*dir;
	struct dirent	*file;
	t_list			*files;


	dir = opendir(path);
	if (dir == NULL)
	{
		perror("opendir");
		return (NULL);
	}
	files = NULL;
	while ((file = readdir(dir)))
	{
		lst_push_back(&files, ft_strdup(file->d_name));
	}
	lst_b_sort(&files, &ft_strcmp, 0);
	closedir(dir);
	return (files);
}

void
send_ls(t_socket *sock, const char *dir)
{
	t_list			*files;
	uint32_t		size;
	SOCK_ERR		sock_err;
	t_list			*lstwalker;

	files = list_dir(dir);
	size = lst_count(files);
	sock_err = send(sock->sock, &size, sizeof(uint32_t), 0);
	if (sock_err == -1)
		perror("send_ls size");
	lstwalker = files;
	while (lstwalker != NULL)
	{
		sock_err = send_msg(sock->sock, (char *)lstwalker->data);
		if (sock_err == -1)
			perror("send_ls file");
		if (lstwalker->next == NULL)
			break ;
		lstwalker = lstwalker->next;
	}
	lst_free(&files, 1);
}

void
talk(t_socket *csock, int *run, int *connected)
{
	char	*msg;

	if ((msg = rec_msg(csock->sock)) != NULL)
	{
		printf("receive command : \"%s\"\n", msg);

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