#include <errno.h>
#include <stdio.h>

#include <libft.h>
#include <libftsocket.h>

int					send_msg(const int fd, char *msg)
{
	int				len;

	len = ft_strlen(msg);
	if (send_uint32(fd, len) == -1)
		return (-1);
	if (send(fd, &(*msg), sizeof(char) * len, 0) != len)
	{
		perror("Error while sending msg");
		return (-1);
	}
	return (0);
}

char				*get_msg(const int fd)
{
	uint32_t		len;
	char			*msg;
	uint32_t		n;

	len = get_uint32(fd);
	if (!(msg = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	n = 0;
	while ((n += recv(fd, &(*msg) + n, sizeof(char) * len, 0)) < len);
	msg[len] = '\0';
	return (msg);
}