#include <stdlib.h>

#include <sys/stat.h>

#include <errno.h>
#include <stdio.h>

#include <libftsocket.h>

int						send_data(const int fd, void *data, int size)
{
	if (send_int32(fd, size) == -1)
		return (-1);
	if (send(fd, data, size, 0) == -1)
	{
		perror("Error sending data");
		return (-1);
	}
	return (0);
}

int						get_data(const int fd, void **data)
{
	int					size;
	int					i;

	size = get_int32(fd);
	if (!(*data = malloc(size)))
		return (-1);
	i = 0;
	while (i < size)
	{
		i += recv(fd, *data + i, BUFSIZ, 0);
	}
	return (size);
}