#include <libftsocket.h>

int					send_msg_type(const int fd, const t_msg_type type)
{
	int				n;

	n = send(fd, &type, sizeof(type), 0);
	return (n);
}

t_msg_type			get_msg_type(const int fd)
{
	t_msg_type		type;

	recv(fd, &type, sizeof(type), 0);
	return (type);
}