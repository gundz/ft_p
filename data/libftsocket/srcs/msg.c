#include <libftsocket.h>
#include <libft.h>

char *
rec_msg(SOCK socket)
{
	int		size;
	int		n;
	char	*msg;

	ft_strlen("test");
	n = recv(socket, &size, sizeof(int), 0);
	if (n == -1)
	{
		perror("msg size");
		return (NULL);
	}
	if (!(msg = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	n = recv(socket, msg, size, 0);
	msg[n] = '\0';
	if (n == -1)
	{
		perror("msg");
		free(msg);
		return (NULL);
	}
	return (msg);
}

SOCK_ERR
send_msg(SOCK socket, char *msg)
{
	SOCK_ERR	sock_err;
	int			size;

	sock_err = 0;
	size = ft_strlen(msg);
	if (size > 0)
	{
		sock_err = send(socket, &size, sizeof(int), 0);
		if (sock_err == -1)
			perror("send_msg size");
		sock_err = send(socket, &(*msg), size, 0);
		if (sock_err == -1)
			perror("send_msg");
	}
	return (sock_err);
}

SOCK_ERR
send_msg_input(SOCK socket, char **input)
{
	SOCK_ERR	sock_err;

	ft_putstr("$>: ");
	get_next_line(0, input);
	sock_err = send_msg(socket, *input);
	return (sock_err);
}