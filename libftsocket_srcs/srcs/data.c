#include <stdlib.h>

#include <sys/stat.h>

#include <errno.h>
#include <stdio.h>

#include <libftsocket.h>

int						send_data(const int fd, void *data, size_t size)
{
	if (send_uint32(fd, size) == -1)
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

	size = get_uint32(fd);
	if (!(*data = malloc(size)))
		return (-1);
	i = 0;
	while (i < size)
	{
		i += recv(fd, *data + i, DATA_BUF_SIZE, 0);
	}
	return (size);
}