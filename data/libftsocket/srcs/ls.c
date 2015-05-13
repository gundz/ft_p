#include <libftsocket.h>
#include <libft.h>
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
