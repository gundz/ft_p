#include <errno.h>
#include <stdio.h>

#include <libftsocket.h>

int					send_int32(const int fd, const int32_t var)
{
	if (send(fd, &var, sizeof(int32_t), 0) == -1)
	{
		perror("Error sending int32_t");
		return (-1);
	}
	return  (0);
}

int					get_int32(const int fd)
{
	int32_t		var;

	if (recv(fd, &var, sizeof(int32_t), 0) == -1)
	{
		perror("Error getting int32_t");
	}
	return (var);
}